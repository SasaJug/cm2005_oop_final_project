/*
  ==============================================================================

    PlaylistComponent.cpp
    Created: 4 Aug 2024 4:16:24pm
    Author:  Sasa Jugurdzija, from initial version implemented in the course.

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistComponent.h"

//==============================================================================
PlaylistComponent::PlaylistComponent(DJAudioPlayer* _player, int _side)
    : player(_player), side(_side)
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

void PlaylistComponent::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void PlaylistComponent::resized()
{
    tableComponent.getHeader().setColumnWidth(0, getWidth() * 0.90);
    tableComponent.getHeader().setColumnWidth(1, getWidth() * 0.10);
    int buttonHeight = 30;
    tableComponent.setBounds(0, 0, getWidth(), getHeight() - buttonHeight);
    addButton.setBounds(0, getHeight() - buttonHeight, getWidth() / 4, buttonHeight);
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
    if (rowIsSelected)
    {
        g.fillAll(Colours::orange);
    }
    else
    {
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
    if (lastRowSelected == previouslySelectedRow)
        return;

    if (lastRowSelected >= 0)
    {
        tableComponent.selectRow(lastRowSelected);
        URL url = URL{ trackTitles[lastRowSelected] };
        player->loadURL(url);
        EventBus::getInstance().triggerEvent(
            EventTypes::FILE_LOADED_EVENT,
            std::to_string(side) + "," + url.toString(false).toStdString()); // payload: "side,url"
    }

    previouslySelectedRow = lastRowSelected;
}

void PlaylistComponent::cellClicked(int rowNumber, int columnId, const MouseEvent&)
{
    DBG("Cell clicked: " + std::to_string(columnId));
    tableComponent.selectRow(rowNumber);
}

Component* PlaylistComponent::refreshComponentForCell(int rowNumber,
    int columnId,
    bool isRowSelected,
    Component* existingComponentToUpdate)
{
    if (columnId == 1)
    {
        if (existingComponentToUpdate == nullptr)
        {
            TextButton* btn = new TextButton{ "x" };
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
        auto fileChooserFlags = FileBrowserComponent::canSelectFiles;
        fChooser.launchAsync(fileChooserFlags, [this](const FileChooser& chooser)
            {
                File chosenFile = chooser.getResult();
                URL url = URL{ chosenFile };
                trackTitles.push_back(chosenFile);
                tableComponent.updateContent();
            });
    }
    else
    {
        int id = std::stoi(button->getComponentID().toStdString());
        int currentlySelectedRow = tableComponent.getSelectedRow();

        if (id == currentlySelectedRow)
        {
            player->stop();
            player->setPositionRelative(0.0);
            player->unload();
            tableComponent.deselectAllRows();
            EventBus::getInstance().triggerEvent(
                EventTypes::CURRENT_FILE_REMOVED,
                std::to_string(side) // payload: "side"
            );
        }

        trackTitles.erase(trackTitles.begin() + id);

        if (currentlySelectedRow > id && currentlySelectedRow > 0)
        {
            currentlySelectedRow--;
        }

        tableComponent.updateContent();

        if (currentlySelectedRow >= 0 && currentlySelectedRow < trackTitles.size())
        {
            tableComponent.selectRow(currentlySelectedRow);
        }
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
