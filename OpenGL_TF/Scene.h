#pragma once
#include "Camera.h"
#include "Model.h"

#include <vector>

class Scene
{
public:
    //default constructor
    Scene()
    {

    }

    ~Scene()
    {

    }

    void AttachCamera(Camera* sCamera)
    {
        CurrentCamera = sCamera;
    }

    void AddModel(Model* model)
    {
        ModelList.push_back(model);
    }

    void Draw()
    {
        for(auto model:ModelList)
        {
            //model->Draw();
        }
    }




private:
    Camera* CurrentCamera;
    std::vector<Model*> ModelList;
};