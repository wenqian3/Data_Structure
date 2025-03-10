
#include "cs225/PNG.h"
#include <list>
#include <iostream>
#include <vector>
#include "colorPicker/ColorPicker.h"
#include "imageTraversal/ImageTraversal.h"

#include "Point.h"
#include "Animation.h"
#include "FloodFilledImage.h"

#include <queue>

using namespace cs225;

/**
 * Constructs a new instance of a FloodFilledImage with a image `png`.
 *
 * @param png The starting image of a FloodFilledImage
 */
FloodFilledImage::FloodFilledImage(const PNG & png) {
    /** @todo [Part 2] */
    myPNG = png;
}

/**
 * Adds a flood fill operation to the FloodFillImage.  This function must store the operation,
 * which will be used by `animate`.
 *
 * @param traversal ImageTraversal used for this FloodFill operation.
 * @param colorPicker ColorPicker used for this FloodFill operation.
 */
void FloodFilledImage::addFloodFill(ImageTraversal & traversal, ColorPicker & colorPicker) {
    /** @todo [Part 2] */

    ImageTraversal *traversalTemp = &traversal;
    ColorPicker *colorTemp = &colorPicker;
    myTraversal.push_back(traversalTemp);
    myColor.push_back(colorTemp);
}

/**
 * Creates an Animation of frames from the FloodFill operations added to this object.
 *
 * Each FloodFill operation added by `addFloodFill` is executed based on the order
 * the operation was added.  This is done by:
 * 1. Visiting pixels within the image based on the order provided by the ImageTraversal iterator and
 * 2. Updating each pixel to a new color based on the ColorPicker
 *
 * While applying the FloodFill to the image, an Animation is created by saving the image
 * after every `frameInterval` pixels are filled.  To ensure a smooth Animation, the first
 * frame is always the starting image and the final frame is always the finished image.
 *
 * (For example, if `frameInterval` is `4` the frames are:
 *   - The initial frame
 *   - Then after the 4th pixel has been filled
 *   - Then after the 8th pixel has been filled
 *   - ...
 *   - The final frame, after all pixels have been filed)
 */
Animation FloodFilledImage::animate(unsigned frameInterval) const {

    Animation animation;
    animation.addFrame(myPNG);

    for (unsigned i = 0; i < myTraversal.size(); i++) {
        ImageTraversal *traversal = myTraversal[i];
        ColorPicker *newcolor = myColor[i];
        unsigned count = frameInterval;

        for (ImageTraversal::Iterator it = traversal->begin(); it != traversal->end(); ++it) {
            HSLAPixel &pixel = myPNG.getPixel((*it).x, (*it).y);
            HSLAPixel pixel1 = newcolor->getColor((*it).x, (*it).y);

            pixel.h = pixel1.h;
            pixel.l = pixel1.l;
            pixel.s = pixel1.s;
            pixel.a = pixel1.a;
            count--;
            if (count == 0) {
                animation.addFrame(myPNG);
                count = frameInterval;
            }
        }

        animation.addFrame(myPNG);
    }

    return animation;
}



