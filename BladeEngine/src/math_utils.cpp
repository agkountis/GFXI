#include "math_utils.h"

using namespace Blade::MathUtils;

Derivative RungeKutta4Integrator::Evaluate(const State& initial, float timeSec, float deltaTime, const Derivative& derivative) noexcept
{
	State state;
	state.x = initial.x + derivative.dx * deltaTime;
	state.v = initial.v + derivative.dv * deltaTime;
	state.force = initial.force;
	state.mass = initial.mass;

	Derivative output;
	output.dx = state.v;
	output.dv = state.force / state.mass;
	return output;
}


State RungeKutta4Integrator::Integrate(const State& state, float timeSec, float deltaTime) noexcept
{
	Derivative a, b, c, d;

	a = Evaluate(state, timeSec, 0.0f, Derivative{});
	b = Evaluate(state, timeSec, deltaTime * 0.5f, a);
	c = Evaluate(state, timeSec, deltaTime * 0.5f, b);
	d = Evaluate(state, timeSec, deltaTime, c);

	float dxdt = 1.0f / 6.0f * (a.dx + 2.0f * (b.dx + c.dx) + d.dx);

	float dvdt = 1.0f / 6.0f * (a.dv + 2.0f * (b.dv + c.dv) + d.dv);

	State res;
	res.x = state.x + dxdt * deltaTime;
	res.v = state.v + dvdt * deltaTime;

	return res;
}


void RungeKutta4Integrator::Integrate(Vec3f& position, Vec3f& velocity, const Vec3f& force, float mass, float timeSec, float deltaTime) noexcept
{
	State stateX;
	stateX.x = position.x;
	stateX.v = velocity.x;
	stateX.force = force.x;
	stateX.mass = mass;

	State stateY;
	stateY.x = position.y;
	stateY.v = velocity.y;
	stateY.force = force.y;
	stateY.mass = mass;

	State stateZ;
	stateZ.x = position.z;
	stateZ.v = velocity.z;
	stateZ.force = force.z;
	stateZ.mass = mass;

	stateX = Integrate(stateX, timeSec, deltaTime);
	stateY = Integrate(stateY, timeSec, deltaTime);
	stateZ = Integrate(stateZ, timeSec, deltaTime);

	position = Vec3f{ stateX.x, stateY.x, stateZ.x };

	velocity = Vec3f{ stateX.v, stateY.v, stateZ.v };
}