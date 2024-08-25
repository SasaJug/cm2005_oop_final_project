/*
  ==============================================================================

    PlaylistComponent.h
    Created: 4 Aug 2024 4:16:24pm
    Author:  jugur

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include "DJAudioPlayer.h"
#include "EventBus.h"
#include "EventTypes.h"
using namespace juce;

//==============================================================================
/*
*/
class PlaylistComponent  : public juce::Component,
                           public TableListBoxModel,
                           public FileDragAndDropTarget,
                           public Button::Listener
{
public:
    PlaylistComponent(DJAudioPlayer* _player, int position);

    ~PlaylistComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    int getNumRows() override;

    void paintRowBackground(Graphics&,
        int rowNumber,
        int width,
        int height,
        bool rowIsSelected) override;

    void paintCell(Graphics&,
        int rowNumber,
        int columnId,
        int width,
        int height,
        bool rowIsSelected) override;

    void selectedRowsChanged(int lastRowSelected) override;


    void cellClicked(int rowNumber, int columnId, const MouseEvent&) override;

    void buttonClicked(Button* button) override;

    Component* refreshComponentForCell(int rowNumber,
        int columnId,
        bool isRowSelected,
        Component* existingComponentToUpdate) override;

    bool isInterestedInFileDrag(const StringArray& files) override;
    void filesDropped(const StringArray& files, int x, int y) override;


private:
    juce::FileChooser fChooser{ "Select a file..." };

    int position;

    TableListBox tableComponent;
    std::vector<File> trackTitles;

    std::unique_ptr<juce::Drawable> deleteDrawable;

    DJAudioPlayer* player;

    juce::TextButton addButton{ "ADD" };


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
