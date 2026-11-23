// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <cstdint>

namespace Libraries::AudioOut {

// Report supported speaker counts from the opened SDL playback device.
// Unsupported or unknown layouts retain safe stereo.
[[nodiscard]] constexpr std::uint8_t SelectGuestSpeakerChannels(int host_channels) {
    switch (host_channels) {
    case 6: // 5.1
        return 6;
    case 8: // 7.1
        return 8;
    default:
        return 2; // stereo, mono and unsupported speaker arrangements
    }
}

} // namespace Libraries::AudioOut
