#define _CRT_SECURE_NO_WARNINGS
#include "UserBoard.h"

UserBoard::UserBoard(RenderWindow& window,
    Vector2f center,
    Vector2f size,
    Vector2f vpSizeRatio,
    Vector2f vpLocationRatio) :
    DrawingBoard(window, center, size, vpSizeRatio, vpLocationRatio)
{
}

void UserBoard::Capture()
{
    if (drawingTex.getTexture().copyToImage().saveToFile(DRAWINGS + charFilename))
    {
        cout << FILE_SAVED_TO << DRAWINGS << charFilename << endl;
        // Creates a copy of the filename and changes it to a .dat file
        string txtName = charFilename;
        txtName.replace(txtName.find_last_of("."), txtName.length(), FILE_TYPE);
        txtName = BINARIES + txtName;
        float rotInfo;
        // Writing to current file
        FILE* txtFile;
        txtFile = fopen(txtName.c_str(), "w");
        if (txtFile == NULL)
            cout << ERROR_WHILE_OPENING << endl;
        for (auto& line : mainLines)
        {
            fprintf(txtFile, "%f\n%f\n", line.getSize().x, line.getSize().y);
            fprintf(txtFile, "%f\n%f\n", line.getPosition().x, line.getPosition().y);
            fprintf(txtFile, "%f\n", line.getRotation());
        }
        fclose(txtFile);
    }
    else
        cout << ERROR_ACCURED << endl;
}
