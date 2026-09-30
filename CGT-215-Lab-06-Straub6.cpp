#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

int main() {
    //This section allows for the code to look for the images in the files
    string background = "images1 (1)/backgrounds/winter.png";
    string foreground = "images1 (1)/characters/yoda.png";

    Texture backgroundTex;

    if (!backgroundTex.loadFromFile(background)) {
        cout << "Couldn't Load Image" << endl;
        exit(1);
    }

    Texture foregroundTex;

    if (!foregroundTex.loadFromFile(foreground)) {
        cout << "Couldn't Load Image" << endl;
        exit(1);
    }

    Image backgroundImage;
    backgroundImage = backgroundTex.copyToImage();

    Image foregroundImage;
    foregroundImage = foregroundTex.copyToImage();

    Vector2u sz = backgroundImage.getSize();

    // Get the green-screen color from the corner of the foreground image
    Color greenScreenColor = foregroundImage.getPixel(0, 0);

    // Go through every pixel in the images
    for (int y = 0; y < sz.y; y++) {
        for (int x = 0; x < sz.x; x++) {

            // Get the current foreground pixel
            Color foregroundPixel = foregroundImage.getPixel(x, y);

            // If the pixel is the green-screen color,
            // replace it with the corresponding background pixel
            if (foregroundPixel == greenScreenColor) {
                Color backgroundPixel = backgroundImage.getPixel(x, y);
                foregroundImage.setPixel(x, y, backgroundPixel);
            }
        }
    }

    // Display the composited image
    RenderWindow window(VideoMode(1024, 768), "Here's the output");

    Sprite sprite1;
    Texture tex1;

    tex1.loadFromImage(foregroundImage);
    sprite1.setTexture(tex1);

    window.clear();
    window.draw(sprite1);
    window.display();

    while (true);
}