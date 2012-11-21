#include "MapNode.h"

namespace csci561
{
    void MapNode::getPathFromRoot(std::vector<MapNode *> &path)
    {
        MapNode *node = this;

        //parent of node should be null, so the while below will include root
        while(node)
        {
            path.push_back(node);
            node = node->getParent();
        }
    }

}
