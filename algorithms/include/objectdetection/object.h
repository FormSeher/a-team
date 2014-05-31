#ifndef FS_OBJECT_H
#define FS_OBJECT_H

#include "objectdetection/model.h"

namespace formseher
{

class Object : public Model
{
public:
    Object();

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
    float rating;
};

} // namespace formseher

#endif // FS_OBJECT_H
