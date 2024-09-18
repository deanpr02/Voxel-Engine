#include "lighting.h"

extern Shaders _shaders;
//TODO: update rotation of the flashlight so front of cube points in the direction we are looking
glm::mat4 LightingSystem::rotateLightToCamera(const glm::vec3& lightPos, const glm::vec3& cameraDir, const glm::vec3& upVector){
    glm::vec3 targetPos = lightPos + cameraDir;
    glm::mat4 model = glm::lookAt(lightPos,targetPos,upVector);
    model = glm::inverse(model);
    model= glm::scale(model,glm::vec3(-1.0f,1.0f,1.0f));
    return model;
}

void LightingSystem::adjustFlashlight(Shader lightShader,Camera camera){
    lightShader.use();
    lightShader.setMat4("perspective",camera._projMatrix);
    lightShader.setMat4("view",camera.getViewMatrix());
    glm::mat4 lightModel = glm::mat4(1.0f);
    glm::vec3 camDirection = glm::vec3(camera._direction.i,camera._direction.j,camera._direction.k);
    camDirection += camera._up * -0.4f;
    camDirection += camera._right * 0.4f;
    _flashlightPos = camera._pos + camDirection;
    lightModel = glm::translate(lightModel,_flashlightPos);
    //lightModel = rotateLightToCamera(_flashlightPos,camDirection,camera._up);
    lightModel = glm::scale(lightModel,glm::vec3(0.25f));
    lightShader.setMat4("model",lightModel);
    glDrawArrays(GL_TRIANGLES,0,36);
}

void LightingSystem::setAmbientLighting(Shader shader, float strength){
    //float ambientStrength = 0.1;
    //vec3 objectColor = vec3(0.8f,0.8f,0.8f);
    //vec3 lightColor = vec3(1.0f,1.0f,1.0f);
    shader.use();
    shader.setFloat("ambientStrength",strength);
    shader.setVec3("lightColor",_flashlightColor.x,_flashlightColor.y,_flashlightColor.z);
}

//right now we use the position vector of the light however we probably want to use the direction of the flashlight we want as our position vector so we get a sort
//shining of the light
void LightingSystem::setDiffuseLighting(Shader shader,Camera camera){
    shader.use();
    //glm::vec3 flashDir = glm::vec3(_flashlightPos.x,_flashlightPos.y,_flashlightPos.z) + glm::vec3(camera._forward.i,camera._forward.j,camera._forward.k);
    //shader.setVec3("lightPos",flashDir.x,flashDir.y,flashDir.z);
    shader.setVec3("lightPos",_flashlightPos.x,_flashlightPos.y,_flashlightPos.z);
    
}

void LightingSystem::setSpecularLighting(Shader shader, Camera camera, float strength){
    shader.use();
    shader.setVec3("viewPos",camera._pos.x,camera._pos.y,camera._pos.z);
    shader.setFloat("specularStrength",strength);
}

void LightingSystem::phongAlgorithm(Camera camera){
    //set the ambient lighting for walls
    setAmbientLighting(_shaders.s_wall,0.1f);
    //set diffuse lighting for walls (OMITTED FOR NOW)
    setDiffuseLighting(_shaders.s_wall,camera);
    //set specular lighting for walls
    setSpecularLighting(_shaders.s_wall,camera,0.5);

}