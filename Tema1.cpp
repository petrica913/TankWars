#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2D.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 corner = glm::vec3(0, 0, 0);
    float squareSide = 1;

    cx = corner.x + squareSide / 2;
    cy = corner.y + squareSide / 2;

    translateX = 0;
    translateY = 0;

    scaleX = 1;
    scaleY = 1;

    // Initialize angularStep
    angularStep = 0;

    dir = true;

	amplitude1 = 0.5f;
	amplitude2 = 2.0f;
    amplitude3 = 0.5f;

    freq1 = 1.0f;
	freq2 = 0.20f;
	freq3 = 2.0f;

    numPoints = 200;
    spacing = 0.1f;

    for (int i = 0; i < numPoints; i++) {
        float x = i * spacing;
        float y = amplitude1 * sin(freq1 * x) + amplitude2 * sin(freq2 * x) + amplitude3 * sin(freq3 * x);
        terrainPoints.push_back(y);
    }

    float minY = *std::min_element(terrainPoints.begin(), terrainPoints.end());
    float offsetY = abs(minY);

	for (int i = 0; i < numPoints; i++) {
		terrainPoints[i] += offsetY + 1;
	}

    Mesh* square1 = object2D::CreateSquare("square1", corner, squareSide, glm::vec3(0.792f, 1, 0), true);
    AddMeshToList(square1);
}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0.0f, 0.917f, 1.0f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->GetResolution();
    
    for (int i = 0; i < terrainPoints.size() - 1; i++) {
        float x1 = i * spacing;
        float y1 = terrainPoints[i];
        float x2 = (i + 1) * spacing;
        float y2 = terrainPoints[i + 1];

		glm::mat3 modelMatrix = glm::mat3(1);

		modelMatrix *= transform2D::Translate(x1*75, y1*75);
		modelMatrix *= transform2D::Shear(x1, x2, y1, y2);
        modelMatrix *= transform2D::Scale((x2 - x1) * 75 ,  max(y2, y1) * 75);

		modelMatrix *= transform2D::Translate(0, -1);

        RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);
    }

}


void Tema1::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
