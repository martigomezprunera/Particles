#include <imgui\imgui.h>
#include <imgui\imgui_impl_sdl_gl3.h>

//VARIABLES
bool show_test_window = false;
bool checked = false;
static char text1[8] = "";

//Emitter
float EmitterRate;


void GUI() {
	bool show = true;
	ImGui::Begin("Physics Parameters", &show, 100);

	// Do your GUI code here....
	{	
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);//FrameRate
		
		//Play Simulation (CheckBox)
		if (ImGui::Checkbox("Play Simulation", &checked))
		{

		}

		//Reset Simulation
			//Si presionamos boton
		if (ImGui::Button("Reset Simulation"))
		{

		}

		//Emitter
		ImGui::SetNextTreeNodeOpen(true, ImGuiSetCond_Once);
		if (ImGui::TreeNode("Emitter"))
		{
			ImGui::InputFloat("Emmiter Rate", EmitterRate, sizeof(EmitterRate));

			ImGui::TreePop();
		}

		//Elasticity & Friction
		ImGui::SetNextTreeNodeOpen(true, ImGuiSetCond_Once);
		if (ImGui::TreeNode("Elasticity & Friction"))
		{
			

			ImGui::TreePop();
		}

		//Colliders
		ImGui::SetNextTreeNodeOpen(true, ImGuiSetCond_Once);
		if (ImGui::TreeNode("Colliders"))
		{
			//Use Sphere Collider (CheckBox)

			//Use Capsule Collider (CheckBox)

			ImGui::TreePop();
		}

		
		//Forces
		ImGui::SetNextTreeNodeOpen(true, ImGuiSetCond_Once);
		if (ImGui::TreeNode("Forces"))
		{
			//Use Gravity (CheckBox)

			ImGui::TreePop();
		}
	}
	// .........................
	
	ImGui::End();

	// Example code -- ImGui test window. Most of the sample code is in ImGui::ShowTestWindow()
	if(show_test_window) {
		ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
		ImGui::ShowTestWindow(&show_test_window);
	}
}

void PhysicsInit() {
	// Do your initialization code here...
	// ...................................
}

void PhysicsUpdate(float dt) {
	// Do your update code here...
	// ...........................
}

void PhysicsCleanup() {
	// Do your cleanup code here...
	// ............................
}