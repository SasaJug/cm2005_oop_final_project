/*
  ==============================================================================

    PlaylistComponent.cpp
    Created: 4 Aug 2024 4:16:24pm
    Author:  jugur

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistComponent.h"

//==============================================================================
PlaylistComponent::PlaylistComponent(DJAudioPlayer* _player, int _position) 
    : player(_player),
      position(_position)
{

    addButton.addListener(this);
    addAndMakeVisible(tableComponent);
    addAndMakeVisible(addButton);
    tableComponent.getHeader().addColumn("Track title", 0, 400);
    tableComponent.getHeader().addColumn("", 1, 200);
    tableComponent.setModel(this);
}

PlaylistComponent::~PlaylistComponent()
{
}

void PlaylistComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
}

void PlaylistComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    tableComponent.getHeader().setColumnWidth(0, getWidth()*0.90);
    tableComponent.getHeader().setColumnWidth(1, getWidth()*0.10);
    int buttonHeight = 30;
    tableComponent.setBounds(0, 0, getWidth(), getHeight()-buttonHeight);
    addButton.setBounds(0, getHeight() - buttonHeight, getWidth()/4, buttonHeight);

}

int PlaylistComponent::getNumRows()
{
    return trackTitles.size();
}

void PlaylistComponent::paintRowBackground(Graphics& g,
    int rowNumber,
    int width,
    int height,
    bool rowIsSelected)
{
    // just highlight selected rows
    if (rowIsSelected)
    {
        g.fillAll(Colours::orange);
    }
    else {
        g.fillAll(Colours::darkgrey);
    }
}

void PlaylistComponent::paintCell(Graphics& g,
    int rowNumber,
    int columnId,
    int width,
    int height,
    bool rowIsSelected)
{
    g.drawText(trackTitles[rowNumber].getFileName(),
        2, 0,
        width - 4, height,
        Justification::centredLeft,
        true);
}

void PlaylistComponent::selectedRowsChanged(int lastRowSelected)
{
    if(lastRowSelected >= 0) {
        tableComponent.selectRow(lastRowSelected);
        URL url = URL{ trackTitles[lastRowSelected] };
        player->loadURL(url);
        EventBus::getInstance().triggerEvent(
            EventTypes::FILE_LOADED_EVENT,
            std::to_string(position) + "," + url.toString(false).toStdString()); // position,url
    }

}

void PlaylistComponent::cellClicked(int rowNumber, int columnId, const MouseEvent&)
{
	tableComponent.selectRow(rowNumber);
}

Component* PlaylistComponent::refreshComponentForCell(
    int rowNumber,
    int columnId,
    bool isRowSelected,
    Component* existingComponentToUpdate)
{
    if (columnId == 1)
    {
        if (existingComponentToUpdate == nullptr)
        {
            TextButton * btn = new TextButton { "x" };
            existingComponentToUpdate = btn;
            String id{ std::to_string(rowNumber) };
            btn->setComponentID(id);
            btn->addListener(this);
        }
    }
    return existingComponentToUpdate;
}

void PlaylistComponent::buttonClicked(Button* button)
{
    if (button == &addButton)
    {
        // this does work in 6.1 but the syntax is a little funky
        // https://docs.juce.com/master/classFileChooser.html#ac888983e4abdd8401ba7d6124ae64ff3
        // - configure the dialogue
        auto fileChooserFlags =
            FileBrowserComponent::canSelectFiles;
        // - launch out of the main thread
        // - note how we use a lambda function which you've probably
        // not seen before. Please do not worry too much about that. 
        fChooser.launchAsync(fileChooserFlags, [this](const FileChooser& chooser)
            {
                File chosenFile = chooser.getResult();
                URL url = URL{ chosenFile };
                trackTitles.push_back(chosenFile);
                tableComponent.updateContent();
                //player->loadURL(url);
                //EventBus::getInstance().triggerEvent(
                //    EventTypes::FILE_LOADED_EVENT,
                //    std::to_string(position) + "," + url.toString(false).toStdString()); // position,url
            });
    }
    else
    {
        int id = std::stoi(button->getComponentID().toStdString());
        DBG("PlaylistComponent::buttonClicked " << trackTitles[id].getFileName() << "");
        if(id == tableComponent.getSelectedRow())
		{
			player->unload();
            tableComponent.deselectAllRows();
		}
        trackTitles.erase(trackTitles.begin() + id);
        tableComponent.updateContent();
    }
}

bool PlaylistComponent::isInterestedInFileDrag(const StringArray& files)
{
    return true;
}

void PlaylistComponent::filesDropped(const StringArray& files, int x, int y)
{
    if (files.size() == 1)
    {
        trackTitles.push_back(files[0]);
        tableComponent.updateContent();
    }
}





