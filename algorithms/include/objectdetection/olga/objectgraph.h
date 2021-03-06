/*
 * This file is part of FormSeher.
 *
 * FormSeher is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * FormSeher is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with FormSeher.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright 2014 FormSeher
 */

#ifndef FS_OBJECTGRAPH_H
#define FS_OBJECTGRAPH_H

#include <map>
#include <set>
#include <opencv2/core/core.hpp>

#include "objectdetection/olga/objectgraphedge.h"
#include "objectdetection/olga/objectgraphnode.h"
#include "pointercompare.h"

namespace formseher
{

class ObjectGraph
{
public:
    ObjectGraph();
    ~ObjectGraph();

    /**
     * @brief Compares this ObjectGraph to another ObjectGraph.
     * @param The ObjectGraph compared against.
     * @return An approximation of how equal the two ObjectGraphs are. Lies between
     * 0.0 (0%) if they are disjunct or 1.0 (100%) if they are equal.
     */
    float compareTo(const ObjectGraph& objectGraph) const;

    /**
     * @brief Insert a new node with given parameters.
     * @param x The x-coordinate of the node.
     * @param y The y-coordinate of the node.
     * @return Pointer to the newly created node.
     */
    ObjectGraphNode *insertNode(int x, int y);

    /**
     * @brief Insert a new edge between two nodes.
     * @param start The start of the edge.
     * @param end The end of the edge.
     * @return Pointer to the newly created edge.
     */
    ObjectGraphEdge* insertEdge(ObjectGraphNode* _start, ObjectGraphNode* _end);

    /**
     * @brief Get the number of nodes added to the graph.
     * @return Number of nodes.
     */
    int getNodeCount() const;

    /**
     * @brief Get the number of edges added to the graph.
     * @return Number of edges.
     */
    int getEdgeCount() const;

    /**
     * @brief Find a node in the graph.
     * @param coordinates The coordinates of the searched node.
     * @return Pointer to the node or null if no node was found.
     */
    ObjectGraphNode* findNode(cv::Point2i coordinates);

    /**
     * @brief Find an edge in the graph.
     * @param start One end of the edge.
     * @param end The other end of the edge.
     * @return Pointer to the edge or null if no edge was found.
     */
    ObjectGraphEdge* findEdge(const ObjectGraphNode* _start, const ObjectGraphNode* _end) const;

    /**
     * @brief Get the bounding box of the Graph.
     *
     * Bounding box of the graph in which all nodes are included.
     *
     * @return The bounding box as cv::Rect.
     */
    cv::Rect getBoundingBox() const;

    /**
     * @brief Get the set of nodes of the graph.
     * @return Set containing the nodes of the graph.
     */
    const std::set<ObjectGraphNode*, PointerCompare<ObjectGraphNode>>& getNodes() const;

    /**
     * @brief Get the vector of edges of the graph.
     * @return Vector containing the edges of the graph.
     */
    const std::set<ObjectGraphEdge*>& getEdges() const;

private:
    std::set<ObjectGraphNode*, PointerCompare<ObjectGraphNode>> nodes;
    std::set<ObjectGraphEdge*> edges;
    // edge map for improved find algorithm
    std::map<const ObjectGraphNode*, std::map<const ObjectGraphNode*, ObjectGraphEdge*>> edgesMap;

    // top-left (0) and bottom-right (1) points of bounding box.
    cv::Point2i boundingBoxCorners[2];

    /**
     * @brief Updates the bounding box.
     *
     * Called after a new node was inserted (@see ObjectGraph::insertNode()). Updates the top-left and
     * bottom-right corners of the bounding box.
     *
     * @param node Pointer to the new inserted ObjectGraphNode.
     */
    void updateBoundingBox(const ObjectGraphNode* node);
};

} // namespace formseher

#endif // FS_OBJECTGRAPH_H
