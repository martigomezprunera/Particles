#include <imgui\imgui.h>
#include <imgui\imgui_impl_sdl_gl3.h>

//VARIABLES
bool show_test_window = false;
bool checkedSimulation = false;
bool checkedGravity = false;
bool checkedSphere = false;
bool checkedCapsule = false;

//Emitter
float EmitterRate;
float ParticleLife;

//Fountain || Cascade
int foc;

//Pos, Dir, Angle
float Pos[3];
float Dir[3];
float Angle;

//Elasticity, Friction
float ElasticCoefficient;
float FrictionCoefficient;

//Colliders
//Sphere
float SpherePos[3];
float SphereRadius;

//Capsule
float CapsulePosA[3];
float CapsulePosB[3];
float CapsuleRadius;

//Forces
float GravityAccel[3];

//Funciones externas
extern void setupPrims();
extern void cleanupPrims();
extern void renderPrims();

void GUI() {
	bool show = true;
	ImGui::Begin("Physics Parameters", &show, 100);

	// Do your GUI code here....
	{	
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);//FrameRate
		
		//Play Simulation (CheckBox)
		ImGui::Checkbox("Play Simulation", &checkedSimulation);
		
		//Call Simulation
		if(checkedSimulation){

		}

		//Call Reset Simulation
			//Si presionamos boton
		if (ImGui::Button("Reset Simulation"))
		{

		}

		//Emitter
		ImGui::SetNextTreeNodeOpen(true, ImGuiSetCond_Once);
		if (ImGui::TreeNode("Emitter"))
		{
			ImGui::InputFloat("Emitter rate", &EmitterRate);
			ImGui::InputFloat("Particle life", &ParticleLife);

			//Fountain || Cascade
			ImGui::RadioButton("Fountain", &foc, 0); 
			ImGui::SameLine();
			ImGui::RadioButton("Cascade", &foc, 1);

			//Pos, Dir, Angle
			ImGui::InputFloat3("Fountain pos", &Pos[0]);
			ImGui::InputFloat3("Fountain dir", &Dir[0]);
			ImGui::InputFloat("Angle", &Angle);

			//Call Function Fountain
			if (foc == 0)
			{

			}

			//Call Function Cascade
			if (foc == 1)
			{

			}
			
			ImGui::TreePop();
		}

		//Elasticity & Friction
		ImGui::SetNextTreeNodeOpen(true, ImGuiSetCond_Once);
		if (ImGui::TreeNode("Elasticity & Friction"))
		{
			ImGui::InputFloat("Elastic Coefficient", &ElasticCoefficient);
			ImGui::InputFloat("Friction Coefficient", &FrictionCoefficient);

			ImGui::TreePop();
		}

		//Colliders
		ImGui::SetNextTreeNodeOpen(true, ImGuiSetCond_Once);
		if (ImGui::TreeNode("Colliders"))
		{
			//Use Sphere Collider (CheckBox)
			ImGui::Checkbox("Use Sphere Collider", &checkedSphere);
			
			if (checkedSphere)
			{
				//Sphere
				ImGui::InputFloat3("Sphere Position", &SpherePos[0]);
				ImGui::InputFloat("Sphere Radius", &SphereRadius);
			}

			//Use Capsule Collider (CheckBox)
			ImGui::Checkbox("Use Capsule Collider", &checkedCapsule);

			if (checkedCapsule)
			{
				//Capsule
				ImGui::InputFloat3("Capsule Pos A", &CapsulePosA[0]);
				ImGui::InputFloat3("Capsule Pos B", &CapsulePosB[0]);
				ImGui::InputFloat("Capsule Radius", &CapsuleRadius);
			}

			ImGui::TreePop();
		}

		
		//Forces
		ImGui::SetNextTreeNodeOpen(true, ImGuiSetCond_Once);
		if (ImGui::TreeNode("Forces"))
		{
			//Use Gravity (CheckBox)
			ImGui::Checkbox("Use Gravity", &checkedGravity);

			if(checkedGravity)
			{
				ImGui::InputFloat3("Gravity Accel", &GravityAccel[0]);
			}

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

	setupPrims();
	
}

void PhysicsUpdate(float dt) {
	// Do your update code here...
	// ...........................

	renderPrims();

}

void PhysicsCleanup() {
	// Do your cleanup code here...
	// ............................

	cleanupPrims();
}