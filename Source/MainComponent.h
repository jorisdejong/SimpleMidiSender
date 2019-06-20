/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainContentComponent   : public Component,
public ComboBox::Listener,
public Button::Listener

{
public:
    //==============================================================================
    MainContentComponent();
    ~MainContentComponent();

    void paint (Graphics&) override;
    void resized() override;
    
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;
    
    void buttonClicked (Button*) override;

private:
    //a comobobox that we can use to select a midioutput
    ComboBox midiOutputList;
    ScopedPointer<Button> sendRandomNote;
    ScopedPointer<Button> sendRandomNoteWithNoteOff;
    ScopedPointer<MidiOutput> midiOutput;
    
    struct MidiNote
    {
        int channel = 1;
        int note = 0;
    };
    
    MidiNote randomNote;
    
    void chooseRandomNote();
   
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
