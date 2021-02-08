#include "Scene.h"

Scene::Scene(QGraphicsScene* parent) : QGraphicsScene(parent)
{
    GraphicsChunkContainer = nullptr;
}

Scene::~Scene()
{

}
