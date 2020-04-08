# pitchshifter
VST plugin to shift pitch in steps of semitones.

This repository contains C++ files to be used within the JUCE Framework (https://juce.com/) to create a VST audio plugin. The plugin applies a phase vocoder algorithm to shift the pitch from -6 to +6 semitones, while maintaining the original tempo. The algorithm is based on a MATLAB example described at https://www.mathworks.com/help/audio/examples/pitch-shifting-and-time-dilation-using-a-phase-vocoder-in-matlab.html. It seems to work OK, although raising the pitch 6 semitones does produce an "Alvin and the Chipmunks" sound.

Here is a rough outline of the steps to build a plugin from this code:

1. Obtain a copy of JUCE. They offer a free version and this is the version that I use.
2. Start JUCE and select File/New Project.
3. See JUCE documentation to see how to set up the project. To keep things simple, name your project PitchShifter.
4. Download the files from the repository to the Source folder of the JUCE project. You may have to clear the folder first or overwrite stuff that JUCE put there.
5. Use Add Existing Files to add the repository files to your project.
6. Hit "Save and Open in IDE" and see if it builds!

Good luck!
