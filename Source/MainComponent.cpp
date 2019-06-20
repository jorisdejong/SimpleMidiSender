/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"


//==============================================================================
MainContentComponent::MainContentComponent()
{
    addAndMakeVisible (midiOutputList);
    midiOutputList.setTextWhenNoChoicesAvailable ("No MIDI Output Enabled");
    midiOutputList.addItemList (MidiOutput::getDevices(), 1);
    midiOutputList.addListener (this);
    
    sendRandomNote = new TextButton("Send Sysex");
    addChildComponent( sendRandomNote );
    sendRandomNote->addListener(this);

    midiOutput = nullptr;
    
    setSize (180, 100);
    
    chooseRandomNote();
}

MainContentComponent::~MainContentComponent()
{
    midiOutput = nullptr;
}

void MainContentComponent::paint (Graphics& g)
{
    g.fillAll (Colour (0xff001F36));
}

void MainContentComponent::resized()
{
    Rectangle<int> area (getLocalBounds());
    midiOutputList.setBounds (area.removeFromTop (36).removeFromLeft (180).reduced (8));
    sendRandomNote->setBounds (area.removeFromTop( 36).removeFromLeft(180).reduced(8) );
//    sendRandomNoteWithNoteOff->setBounds (area.removeFromTop( 36).removeFromLeft(180).reduced(8) );
}

void MainContentComponent::comboBoxChanged(juce::ComboBox *comboBoxThatHasChanged)
{
    if ( comboBoxThatHasChanged == &midiOutputList )
        midiOutput = MidiOutput::openDevice( midiOutputList.getSelectedItemIndex() );

    sendRandomNote->setVisible( midiOutput != nullptr );
//    sendRandomNoteWithNoteOff->setVisible( midiOutput != nullptr );
}

void MainContentComponent::buttonClicked(juce::Button *b)
{
    if ( b == sendRandomNote )
    {
        if ( midiOutput )
        {
            //choose a new randomNote
            //chooseRandomNote();
            
            //send a note on with this value
           
            const uint8 buf[] = { 0x00, 0x20, 0x29, 0x02, 0x18, 0x22, 0x02 };
            midiOutput->sendMessageNow(MidiMessage::createSysExMessage(buf, 7));
        }
    }
    
    else if ( b == sendRandomNoteWithNoteOff )
    {
        if ( midiOutput )
        {
            //choose a new randomNote
            //chooseRandomNote();
            
            //send a noteoff for the previous randomnote
            midiOutput->sendMessageNow( MidiMessage::noteOff(randomNote.channel, randomNote.note, 0.0f));
            
            //choose a new randomNote
            //chooseRandomNote();
            
            //send a note on with this value
            midiOutput->sendMessageNow( MidiMessage::noteOn(randomNote.channel, randomNote.note, 1.0f));
        }

    }
}

void MainContentComponent::chooseRandomNote()
{
    randomNote.channel = rand() % 16 + 1;
    randomNote.note = rand() % 127;
}
