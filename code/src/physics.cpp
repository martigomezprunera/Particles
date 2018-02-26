#include <imgui\imgui.h>
#include <imgui\imgui_impl_sdl_gl3.h>
#include <iostream>
#include <stdlib.h>


namespace LilSpheres {
	extern void setupParticles(int numTotalParticles, float radius = 0.05f);
	extern void updateParticles(int startIdx, int count, float* array_data);
	extern void cleanupParticles();
};



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
float Velocity[3];

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

//Cascada variables
float myCascade[3000];
float *ptrParticles;
int numParticles;

//Auxiliares velocidades
float velocidad[300];
bool colisionado;

//D del plano
float d;

//vector normal
float vNormal[3];

//Auxiliares posiciones
float auxPos[3000];
float auxVel[3000];

void GUI() {
	bool show = true;
	ImGui::Begin("Physics Parameters", &show, 100);

	// Do your GUI code here....
	{
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);//FrameRate

																																  //Play Simulation (CheckBox)
		ImGui::Checkbox("Play Simulation", &checkedSimulation);

		//Call Simulation
		if (checkedSimulation) {

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
			ImGui::InputFloat3("Fountain velocity", &Velocity[0]);

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
			else
			{

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
			else
			{

			}

			ImGui::TreePop();
		}


		//Forces
		ImGui::SetNextTreeNodeOpen(true, ImGuiSetCond_Once);
		if (ImGui::TreeNode("Forces"))
		{
			//Use Gravity (CheckBox)
			ImGui::Checkbox("Use Gravity", &checkedGravity);

			if (checkedGravity)
			{
				ImGui::InputFloat3("Gravity Accel", &GravityAccel[0]);
			}

			ImGui::TreePop();
		}
	}
	// .........................

	ImGui::End();

	// Example code -- ImGui test window. Most of the sample code is in ImGui::ShowTestWindow()
	if (show_test_window) {
		ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
		ImGui::ShowTestWindow(&show_test_window);
	}
}

void PhysicsInit() {
	// Do your initialization code here...
	// ...................................
	int i = 0;

	while (i < (3 * 1000))
	{
		//POS X
		myCascade[i] = 2;
		velocidad[i] = -5;
		i++;

		//POS Y
		myCascade[i] = 5;
		velocidad[i] = -2;
		i++;

		//POS Z
		myCascade[i] = ((float)(rand() % 100) / 10) - 5;
		velocidad[i] = 0;
		i++;
	}
	//velocidadiX = ;
	ptrParticles = myCascade;
	numParticles = 100;
}

void PhysicsUpdate(float dt) {
	// Do your update code here...
	// ...........................


	for (int i = 0; i < numParticles; i++)
	{
			//X
			myCascade[i] = myCascade[i] + (dt*velocidad[i]);
			velocidad[i] = velocidad[i] + (dt*(0));
			i++;

			myCascade[i] = myCascade[i] + (dt*velocidad[i]);
			velocidad[i] = velocidad[i] + (dt*(-9.81f));
			i++;

			//Z
			myCascade[i] = myCascade[i] + (dt*velocidad[i]);
			velocidad[i] = velocidad[i] + (dt*(0));
	}

	//Colision
	if (myCascade[1] <= 0)
	{
		//D
		d = 0;

		//Vector normal
		vNormal[0] = 0;
		vNormal[1] = 1;
		vNormal[2] = 0;

		for (int i = 0; i < numParticles; i++)
		{
			myCascade[i] = myCascade[i] - (2 * (vNormal[0] * myCascade[i]) * vNormal[0]);
			velocidad[i] = velocidad[i] - (2 * (vNormal[0] * velocidad[i]) * vNormal[0]);
			i++;

			myCascade[i] = myCascade[i] - (2 * (vNormal[1] * myCascade[i]) * vNormal[1]);
			velocidad[i] = velocidad[i] - (2 * (vNormal[1] * velocidad[i]) * vNormal[1]);
			i++;

			//Z
			myCascade[i] = myCascade[i] - (2 * (vNormal[2] * myCascade[i]) * vNormal[2]);
			velocidad[i] = velocidad[i] - (2 * (vNormal[2] * velocidad[i]) * vNormal[2]);
		}
	}
	else if(myCascade[0] <= -5)
	{

		std::cout << "Chocado" << std::endl;

		//D
		d = 0;

		//Vector normal
		vNormal[0] = 1;
		vNormal[1] = 0;
		vNormal[2] = 0;

		for (int i = 0; i < numParticles; i++)
		{
			myCascade[i] = myCascade[i] - (2 * (vNormal[0] * myCascade[i]) * vNormal[0]);
			velocidad[i] = velocidad[i] - (2 * (vNormal[0] * velocidad[i]) * vNormal[0]);
			i++;

			myCascade[i] = myCascade[i] - (2 * (vNormal[1] * myCascade[i]) * vNormal[1]);
			velocidad[i] = velocidad[i] - (2 * (vNormal[1] * velocidad[i]) * vNormal[1]);
			i++;

			//Z
			myCascade[i] = myCascade[i] - (2 * (vNormal[2] * myCascade[i]) * vNormal[2]);
			velocidad[i] = velocidad[i] - (2 * (vNormal[2] * velocidad[i]) * vNormal[2]);
		}
	}
	else if (myCascade[0] >= 5)
	{
		std::cout << "Chocado" << std::endl;
	}

	LilSpheres::updateParticles(0, numParticles, ptrParticles);
}


void PhysicsCleanup() {
	// Do your cleanup code here...
	// ............................
	LilSpheres::cleanupParticles();

}