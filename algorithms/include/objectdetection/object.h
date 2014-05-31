#ifndef OBJECT_H
#define OBJECT_H

#include <opencv2/core/core.hpp>
#include <string.h>
#include "line.h"

namespace formseher {

class Object
{

public:
    Object();
    Object(const Object& object);

    ~Object();


    void addLine(const Line line);
    const std::vector<const Line*>& getLines() const;

    cv::Rect getBoundingBox() const;

    void setName(std::string name);
    std::string getName() const;

    /**
     * @brief Deserializes Object form string.
     *
     * Take a serialied representation of an Object and initialize this
     * from it. Previously added lines are preserved!
     * Form of the serialized string: @see Object::toString()
     *
     * @param string String of an serialized Object.
     */
    void fromString(const std::string &string);

    /**
     * @brief Serializes Object to string.
     *
     * Following format is used:
     * <name>:<line1>;<line2>;<line3>;
     *
     * Each <lineN> is a serialized Line with following format:
     * <x of start>,<y of start>,<x of end>,<y of end>
     *
     * Example:
     * Fancy object:1,2,3,4;11,22,33,44;
     *
     * @return Serialized Object as string.
     */
    std::string toString();

    /**
     * @brief Sets the rating of the Object.
     * @param rating The rating.
     */
    void setRating(float rating);

    /**
     * @brief Get the rating of the Object.
     * @return The rating.
     */
    float getRating();

private:
    void updateBoundingBox(const cv::Point2i& point);
    cv::Point2i boundingBoxCorners[2];

    std::string name;
    std::vector<const Line*> lines;

    float rating;
};

}   // formseher

#endif // OBJECT_H
