#include "objectdetection/objectdetectionalgorithm.h"
#include "objectdetection/databaseobject.h"

namespace formseher
{

int databaseSize;
std::vector<Object> databaseObjects;

ObjectDetectionAlgorithm::ObjectDetectionAlgorithm()
{
    getAllDatabaseObjects(databaseObjects);
    getDatabaseSize(databaseSize);
}

void getDatabaseSize(int& size){

    // get number of total objects in database
    size = databaseObjects.size();
}

void getAllDatabaseObjects(std::vector<Object>& databaseObjects){

    // @toDo:
    // get somehow all objects in a loop
    // databaseObjects.push_back(...);
}

void getFirstRating(int& rating, Line firstLine, Line secondLine, Object databaseObject){

    // @toDo:
    // compare the distance between start and end points
    // if distance if too high return with 0


    // @toDo:
    // compare the angle of given lines with the angle of first and second line of object
    // how to get lines of a database object:
    //      std::vector<Line> objLines = databaseObject.getLines();
    // do not calculate angles ! takes to much time !
    //      use comparisons instead
    // keep in mind that angles will never match
    //      -> small variances are ok
}

void getRating(int& rating, Object consideredObject, Line lineToCheck, Object databaseObject, int currentLineNumber){

    Line lastFoundLine = consideredObject.getLines()[currentLineNumber-1];
    // currentFoundLine == lineToCheck

    Line lastDBLine = databaseObject.getLines()[currentLineNumber-1];
    Line currentDBLine = databaseObject.getLines()[currentLineNumber];

    // @toDo:
    // compare the distance between start and end points
    // if distance if too high return with 0

    // @toDo:
    // compare the angle of given lines with the angle of first and second line of object
    // do not calculate angles ! takes to much time !
    //      use comparisons instead
    // keep in mind that angles will never match
    //      -> small variances are ok

}

getBestRatedObjects(std::vector<Object> unfinishedObjects, std::vector<Object>& foundObjects){

    // @toDo: iterate through unfinished Objects and get their ratings
    // if rating is above ~80% add it to found objects
    // @reminder: do not only add the best rated object as there could be many same objects in a picture
}

virtual std::vector<Object*> ObjectDetectionAlgorithm::calculate(std::vector<Line> lines){

    std::vector<Object> foundObjects;
    std::vector<Object> unfinishedObjects;

    // iterate through database objects
    for(uint currentObjectIndex = 0; currentObjectIndex < databaseSize; currentObjectIndex++){

        // iterate through received line vector
        // first step: every line equals the first line of a object
        for(uint firstLineIndex = 0; firstLineIndex < lines.size(); firstLineIndex++){

            int rating = 0;

            // second step: match firstLine with all other lines which equal the second line of a object
            for(uint secondLineIndex = 0; secondLineIndex < lines.size(); secondLineIndex++){

            // shorter iteration if comparison between first and second line only needs an angle or distance
            // if relative sizes between lines have to be considered this loop cannot be used
            // for(uint secondLineIndex = firstLineIndex; secondLineIndex < lines.size(); secondLineIndex++){

                // skip same line
                if(firstLineIndex == secondLineIndex){
                    continue;
                }

                // now compare first and second line and rate the likelyhood of the two lines being the first and second line of an object
                getFirstRating(rating, lines[firstLineIndex], lines[secondLineIndex], databaseObjects[currentObjectIndex]);

                // if rating is not high enough continue research
                // @toDo: set appropriate rating value
                if(rating > 0000){

                    // if the first two lines matched add them to found objects vector
                    Object obj;
                    obj.addLine(lines[firstLineIndex]);
                    obj.addLine(lines[secondLineIndex]);
                    unfinishedObjects.push_back(obj);

                    // @toDo: increase overall rating of obj

                    rating = 0;
                }
                else{
                    rating = 0;
                    continue;
                }

            }
        }

        // iterate through lines of an object starting at 3rd line (as first 2 lines are already checked) to check all other lines
        for(uint objectLineIndex = 2; objectLineIndex < databaseObjects[currentObjectIndex].getLines().size(); objectLineIndex++){

            std::vector<Object> newUnfinishedObjects;

            // check other object lines with found lines
            for(uint foundObjectsIndex = 0; foundObjectsIndex < foundObjects.size(); foundObjectsIndex++){

                // get possible next line
                for(uint nextLineIndex = 0; nextLineIndex < lines.size(); nextLineIndex++){

                    int rating;
                    getRating(rating, foundObjects[foundObjectsIndex], lines[nextLineIndex], databaseObjects[currentObjectIndex], objectLineIndex);

                    // if rating is not high enough continue
                    // @toDo: set appropriate rating value
                    if(rating > 0000){

                        // if rating was ok add line to object
                        Object newObj = unfinishedObjects[foundObjectsIndex];
                        newObj.addLine(lines[nextLineIndex]);

                        // @toDo: increase overall rating of obj

                        newUnfinishedObjects.push_back(newObj);
                    }
                    else{
                        continue;
                    }
                }
            }
            unfinishedObjects = newFoundObjects;
        }

    getBestRatedObjects(unfinishedObjects, foundObjects);
    }
    return foundObjects;
}

} // namespace formseher
