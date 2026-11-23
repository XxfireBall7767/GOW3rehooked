// SPDX-License-Identifier: GPL-2.0-or-later
// Standalone: c++ -std=c++17 -Isrc tests/test_auto_surround.cpp -o test_audio
#include <cassert>
#include <cstdint>
#include "orbis/internals/audio/host_surround.h"

int main() {
    using Libraries::AudioOut::SelectGuestSpeakerChannels;
    static_assert(SelectGuestSpeakerChannels(2) == 2);
    static_assert(SelectGuestSpeakerChannels(6) == 6);
    static_assert(SelectGuestSpeakerChannels(8) == 8);
    static_assert(SelectGuestSpeakerChannels(1) == 2);
    static_assert(SelectGuestSpeakerChannels(0) == 2); // device query failed
    static_assert(SelectGuestSpeakerChannels(4) == 2); // unsupported 4.0 layout
    static_assert(SelectGuestSpeakerChannels(7) == 2); // unsupported 6.1 layout
    static_assert(SelectGuestSpeakerChannels(-1) == 2);
    static_assert(SelectGuestSpeakerChannels(3) == 2);
    static_assert(SelectGuestSpeakerChannels(5) == 2);
    static_assert(SelectGuestSpeakerChannels(16) == 2);
    assert(SelectGuestSpeakerChannels(6) == 6);
    assert(SelectGuestSpeakerChannels(8) == 8);
}
