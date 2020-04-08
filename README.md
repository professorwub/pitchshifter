# pitchshifter
VST plugin to shift pitch in steps of semitones.

This repository contains C++ files to be used within the JUCE Framework (https://juce.com/) to create a VST audio plugin. The plugin applies a phase vocoder algorithm to shift the pitch from -6 to +6 semitones, while maintaining the original tempo. The algorithm is based on a MATLAB example described at https://www.mathworks.com/help/audio/examples/pitch-shifting-and-time-dilation-using-a-phase-vocoder-in-matlab.html. It seems to work OK, although raising the pitch 6 semitones does produce an "Alvin and the Chipmunks" sound.
