#include "Resources/Material.hpp"
#include <IMGUI/includes/imgui.h>
#include <IMGUI/includes/imgui_impl_opengl3.h>
#include <IMGUI/includes/imgui_impl_glfw.h>

using namespace Resources;
using namespace std;
using namespace Core::myMath;

Material::Material(Texture* tex, Vec3 color, float shiny) {
	albedoTexture = tex;
	albedoColor = color;
	shininess = shiny;
	specularColor = Vec3(0.8f, 0.8f, 0.8f);
	type = Resource::ResourceType::R_MATERIAL;
	isLoaded = true;
}

void Material::Unload() {

}

void Material::DisplayGUI(int index) {
	ImGui::ColorEdit3(("Albedo Color##" + to_string(index)).c_str(), &albedoColor.x);
	ImGui::ColorEdit3(("Specular Color##" + to_string(index)).c_str(), &specularColor.x);
	ImGui::DragFloat(("Shininess##" + to_string(index)).c_str(), &shininess, 0.1f, 0.1f, 64);
	ImGui::Text("Texture : "); ImGui::SameLine();
	ImGui::Text(albedoTexture ? albedoTexture->name.c_str() : "null");

	if (ImGui::BeginDragDropTarget()) {
		// Enable dropping textures onto materials.
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("0", ImGuiDragDropFlags_SourceAllowNullID)) {
			Texture* droppedNode = *(Texture**)payload->Data; 
			albedoTexture = droppedNode; 
		}
		ImGui::EndDragDropTarget();
	}
	if(albedoTexture && albedoTexture->isLoaded)
		ImGui::Image((ImTextureID)albedoTexture->GetTexKey(), ImVec2(80, 80), ImVec2(0, 1), ImVec2(1, 0), ImVec4(albedoColor.x, albedoColor.y, albedoColor.z, 1));
}