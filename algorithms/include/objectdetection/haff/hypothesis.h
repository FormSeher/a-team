#ifndef FS_HYPOTHESIS_H
#define FS_HYPOTHESIS_H

#include "objectdetection/object.h"

namespace formseher
{

class Hypothesis
{
public:
    /**
     * @brief Hypothesis constructor
     * @param angleWeight Weight factor for angleRating.
     * @param coverWeight Weight factor for coverRating.
     */
    Hypothesis(const Model *model, double angleWeight = 1.0, double coverWeight = 1.0);

    /**
     * @brief Hypothesis copy constructor
     * @param hypothesis Hypothesis where the current should my copied from.
     */
    Hypothesis(const Hypothesis& hypothesis);

    /**
     * @brief Calculates the rating of this Hypothesis.
     */
    void calculateRating();

    /**
     * @brief Returns the rating calculated by calculateRating().
     * @return The weighted rating for this Hypothesis.
     */
    double getRating() const;

    /**
     * @brief Checks if the input image Line line was added previously.
     * @param line A Line detected on the input image.
     * @return True if line was added before otherwise false.
     */
    bool containsLine(const Line* line) const;

    /**
     * @brief Add a new line match.
     * @param pictureLine Line detected on the input image
     * @param databaseLine Line from a database Model.
     */
    void addLineMatch(const Line *pictureLine, const Line *databaseLine);

    /**
     * @brief Compares two Hypothesis by their rating.
     * @param hypo The Hypothesis to compare with this one.
     * @return True if rating of this is less rating of hypo, false otherwise.
     */
    bool operator<(const Hypothesis& hypo) const;

    /**
     * @brief getModel
     * @return Returns the Model which is associated with the Hypothesis.
     */
    const Model* getModel() const;

    /**
     * @brief getLineMatchMap
     * @return Map of matching line pairs.
     */
    const std::map<Line*, Line*> getLineMatchMap() const;

    /**
     * @brief Adds the given line as a line that does not match with the model.
     * @param line Line that gets added.
     */
    void addNotMatchingLines(const Line* line);

private:
    /**
     * @brief Calculates rating of angles.
     * @return Rating of angle match between 0 (0% match) and 1 (100% match).
     */
    double calculateAngleRating();

    /**
     * @brief Calculates the coverage rating for given scale factor.
     * @param scaleFactor Scale factor for which the coverage is calculated.
     * @return Rating of coverage between 0 (0%) and 1 (100%).
     */
    double calculateCoverageRating(double scaleFactor);

    /**
     * @brief Calculates the scaleFactor and coverageRating at once.
     *
     * Coverage calculation internally relies on calculateCoverageRating().
     */
    void calculateScaleAndCoverage();

    /**
     * @brief Calculate the centers of object and model lines.
     * @return Pair which contains center of object as first and center of model as second value.
     */
    std::pair<cv::Point2d, cv::Point2d> calculateCenters();

    /**
     * @brief The scaling of the object related to the matching object.
     */
    double scaleFactor;

    /**
     * @brief Rating value of the line angles.
     */
    double angleRating;

    /**
     * @brief Rating value of the line coverage.
     */
    double coverRating;

    /**
     * @brief The database model this hypothesis gets compared with.
     */
    const Model* model;

    /**
     * @brief Factor with which the angleRating is weighted.
     */
    const double angleWeight;

    /**
     * @brief Factor with which the coverRating is weighted.
     */
    const double coverWeight;

    /**
     * @brief Contains hypothetical matching line pairs (<PictureLine, DB-Line>)
     */
    std::map<Line*, Line*> lineMatchMap;

    /**
     * @brief Contains all model lines that do not match with the image.
     */
    std::vector<const Line*> notMatchingLines;
};

}   // namespace formseher

#endif // FS_HYPOTHESIS_H
