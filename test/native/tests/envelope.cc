// Envelope generator: stage sequencing and the SHOOZ curve presets (M5).
#include "test.h"
#include "shruthi_env.h"

#include <vector>

#include "shruthi/envelope.h"

using namespace shruthi;

namespace {

Envelope env;

// Renders one segment from a fresh trigger and returns the values, one per
// control-rate call, until the stage changes.
std::vector<uint8_t> RenderAttack(uint8_t curve, uint8_t attack) {
  env.Init();
  env.Update(attack, 40, 64, 40);
  env.set_curve(curve);
  env.Trigger(DEAD);
  env.Trigger(ATTACK);
  std::vector<uint8_t> v;
  for (int i = 0; i < 200000 && env.stage() == ATTACK; ++i) {
    v.push_back(env.Render());
  }
  return v;
}

}  // namespace

TEST(EnvelopeStagesStock) {
  env.Init();
  env.Update(10, 20, 64, 30);  // sustain 64 -> level 128
  env.set_curve(0);
  env.Trigger(DEAD);
  env.Trigger(ATTACK);
  uint8_t peak = 0;
  int guard = 0;
  while (env.stage() == ATTACK && ++guard < 100000) {
    uint8_t v = env.Render();
    if (v > peak) peak = v;
  }
  CHECK_EQ(env.stage(), DECAY);
  CHECK(peak >= 250);
  while (env.stage() == DECAY && ++guard < 200000) env.Render();
  CHECK_EQ(env.stage(), SUSTAIN);
  for (int i = 0; i < 100; ++i) CHECK_EQ(env.Render(), 128);
  env.Trigger(RELEASE);
  while (env.stage() == RELEASE && ++guard < 300000) env.Render();
  CHECK_EQ(env.stage(), DEAD);
  CHECK_EQ(env.Render(), 0);
}

TEST(EnvelopeCurvesKeepSegmentDuration) {
  // The curve reshapes a segment; it must not change how long it lasts.
  size_t stock = RenderAttack(0, 60).size();
  CHECK(stock > 100);
  for (uint8_t c = 1; c < 8; ++c) {
    CHECK_EQ(RenderAttack(c, 60).size(), stock);
  }
}

TEST(EnvelopeCurvesAreMonotonicAttacks) {
  for (uint8_t c = 0; c < 8; ++c) {
    std::vector<uint8_t> v = RenderAttack(c, 60);
    for (size_t i = 1; i < v.size(); ++i) {
      CHECK_MSG(v[i] >= v[i - 1], "curve %d: attack drops at %d (%d -> %d)",
                c, (int)i, v[i - 1], v[i]);
    }
    CHECK_MSG(v.back() >= 250, "curve %d ends at %d", c, v.back());
  }
}

TEST(EnvelopeCurvesOrderFromFastToSlowStart) {
  // At a quarter of the attack, preset 0 (exponential, fast start) is
  // highest and each later preset is no higher than the one before.
  std::vector<std::vector<uint8_t> > curves;
  for (uint8_t c = 0; c < 8; ++c) curves.push_back(RenderAttack(c, 60));
  size_t quarter = curves[0].size() / 4;
  for (uint8_t c = 1; c < 8; ++c) {
    CHECK_MSG(curves[c][quarter] <= curves[c - 1][quarter],
              "curve %d (%d) above curve %d (%d) at 1/4", c,
              curves[c][quarter], c - 1, curves[c - 1][quarter]);
  }
  CHECK(curves[0][quarter] > curves[7][quarter] + 64);
}

TEST(EnvelopeLinearCurveIsLinear) {
  std::vector<uint8_t> v = RenderAttack(4, 60);
  for (int k = 1; k < 8; ++k) {
    size_t i = v.size() * k / 8;
    CHECK_NEAR(v[i], 255 * k / 8, 6);
  }
}

TEST(EnvelopeInverseCurveMirrorsStock) {
  // Preset 7 is 1 - e(1 - x): its rise at time t equals the stock curve's
  // remaining distance at time (end - t).
  std::vector<uint8_t> e = RenderAttack(0, 60);
  std::vector<uint8_t> i = RenderAttack(7, 60);
  size_t n = e.size();
  for (int k = 1; k < 8; ++k) {
    size_t t = n * k / 8;
    CHECK_NEAR(i[t], 255 - e[n - 1 - t], 8);
  }
}

TEST(EnvelopeReleaseFromAnyCurveFallsToZero) {
  for (uint8_t c = 0; c < 8; ++c) {
    env.Init();
    env.Update(60, 60, 100, 50);
    env.set_curve(c);
    env.Trigger(DEAD);
    env.Trigger(ATTACK);
    for (int i = 0; i < 100; ++i) env.Render();  // mid-attack
    env.Trigger(RELEASE);
    uint8_t previous = 255;
    int guard = 0;
    while (env.stage() == RELEASE && ++guard < 200000) {
      uint8_t v = env.Render();
      CHECK_MSG(v <= previous, "curve %d: release rises", c);
      previous = v;
    }
    CHECK_EQ(env.stage(), DEAD);
    CHECK_EQ(env.Render(), 0);
  }
}
