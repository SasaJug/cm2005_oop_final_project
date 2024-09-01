/*
  ==============================================================================

    PlaylistComponent.h
    Created: 4 Aug 2024 4:16:24pm
    Author:  Sasa Jugurdzija, from initial version implemented in the course.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include "DJAudioPlayer.h"
#include "EventBus.h"
#include "EventTypes.h"

using namespace juce;

class PlaylistComponent : public juce::Component,
    public TableListBoxModel,
    public FileDragAndDropTarget,
    public Button::Listener
{
public:
    /**
     * @brief Constructor to initialize the PlaylistComponent.
     * @param _player Pointer to the DJAudioPlayer instance.
     * @param _side Indicates which side (1 or 2) this component is on.
     */
    PlaylistComponent(DJAudioPlayer* _player, int _side);

    /**
     * @brief Destructor for PlaylistComponent.
     */
    ~PlaylistComponent() override;

    /**
     * @brief Paints the PlaylistComponent.
     * @param g The Graphics object used for drawing.
     */
    void paint(juce::Graphics& g) override;

    /**
     * @brief Resizes the PlaylistComponent.
     *
     */
    void resized() override;

    /**
     * @brief Returns the number of rows in the table.
     * @return int The number of rows in the table.
     */
    int getNumRows() override;

    /**
     * @brief Paints the background of a table row.
     * @param g The Graphics object used for drawing.
     * @param rowNumber The index of the row to paint.
     * @param width The width of the row.
     * @param height The height of the row.
     * @param rowIsSelected Whether the row is selected or not.
     */
    void paintRowBackground(Graphics& g,
        int rowNumber,
        int width,
        int height,
        bool rowIsSelected) override;

    /**
     * @brief Paints a cell in the table.
     * @param g The Graphics object used for drawing.
     * @param rowNumber The index of the row.
     * @param columnId The ID of the column.
     * @param width The width of the cell.
     * @param height The height of the cell.
     * @param rowIsSelected Whether the row is selected or not.
     */
    void paintCell(Graphics& g,
        int rowNumber,
        int columnId,
        int width,
        int height,
        bool rowIsSelected) override;

    /**
     * @brief Handles row selection changes.
     * @param lastRowSelected The index of the last selected row.
     */
    void selectedRowsChanged(int lastRowSelected) override;

    /**
     * @brief Handles cell click events.
     * @param rowNumber The index of the row that was clicked.
     * @param columnId The ID of the column that was clicked.
     * @param event The MouseEvent object containing details of the click.
     */
    void cellClicked(int rowNumber, int columnId, const MouseEvent& event) override;

    /**
     * @brief Handles button click events.
     * @param button Pointer to the Button that was clicked.
     */
    void buttonClicked(Button* button) override;

    /**
     * @brief Refreshes the component for a specific table cell.
     * @param rowNumber The index of the row.
     * @param columnId The ID of the column.
     * @param isRowSelected Whether the row is selected or not.
     * @param existingComponentToUpdate The existing component to update.
     * @return Component* A pointer to the updated component.
     */
    Component* refreshComponentForCell(int rowNumber,
        int columnId,
        bool isRowSelected,
        Component* existingComponentToUpdate) override;

    /**
     * @brief Checks if the component is interested in file drag-and-drop events. Override from FileDragAndDropTarget
     * @param files The list of files being dragged.
     * @return bool True if the component is interested, otherwise false.
     */
    bool isInterestedInFileDrag(const StringArray& files) override;

    /**
     * @brief Handles files being dropped onto the component. Override from FileDragAndDropTarget
     * @param files The list of files that were dropped.
     * @param x The x-coordinate of the drop location.
     * @param y The y-coordinate of the drop location.
     */
    void filesDropped(const StringArray& files, int x, int y) override;

private:
    juce::FileChooser fChooser{ "Select a file..." };

    int side;
    TableListBox tableComponent;
    std::vector<File> trackTitles;

    std::unique_ptr<juce::Drawable> deleteDrawable;
    DJAudioPlayer* player;

    juce::TextButton addButton{ "ADD" };

    int previouslySelectedRow = -1;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlaylistComponent)
};
