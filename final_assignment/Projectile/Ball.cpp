#include "Ball.h"
#include "SDL_image.h"
#include <iostream>
#include <cmath>


Ball::Ball(double radius, Room *room)
{
	room_ = room;
	radius_ = radius;

	
	v_[0] = 0;
	v_[1] = 0;

	mass_ = 2; // 2kg
	coeff_of_restitution_ = 0.7;
	frictional_force_ = 0.5;	//마찰력:0.95

	Reset();
}

void
Ball::Reset()
{
	p_[0] = radius_ + room_->left_wall_x();
	p_[1] = radius_;

	v_[0] = 0;
	v_[1] = 0;
}

void
Ball::Launch(double initial_force_x, double initial_force_y)
{
	v_[0] = v_[0] + (initial_force_x/mass_);
	v_[1] = v_[1] + (initial_force_y/mass_);
}

void 
Ball::Update(double timestep_s)
{
	double dt = timestep_s;	// seconds
	
	// 가속도
	double a[2];
	a[0] = 0;
	a[1] = room_->gravitational_acc_y();// Gravity(중력)

	// Move
	p_[0] = p_[0] + dt * v_[0];
	p_[1] = p_[1] + dt * v_[1];


	// Collision with Ground(바닥과의 충돌)
	if ( p_[1]-radius_ < room_->ground_height() && v_[1] < 0 ) 
	{
		p_[1] = radius_ + room_->ground_height();

		v_[1] = -1*v_[1];

		// Coefficient of restitution(반발계수)
		v_[1] = coeff_of_restitution_ * v_[1];
	}

	// Collision with Ceilling
	else if ( p_[1]+radius_ > room_->height() && v_[1] > 0 ) 
	{
		p_[1] = room_->height() - radius_;

		v_[1] = -1*v_[1];

		// Coefficient of restitution
		v_[1] = coeff_of_restitution_ * v_[1];
	}

	// Collision with Left Wall(좌측 벽과의 충돌)
	if ( p_[0] - radius_ < room_->left_wall_x() && v_[0] < 0 )
	{
		p_[0] = room_->left_wall_x() + radius_;

		v_[0] = -1 * v_[0];

		// Coefficient of restitution
		v_[0] = coeff_of_restitution_ * v_[0];
	}

	// Collision with Right Wall(우측 벽과의 충돌)
	else if (p_[0] + radius_ > room_->right_wall_x() && v_[0] > 0)
	{
		p_[0] = room_->right_wall_x() - radius_;

		v_[0] = -1 * v_[0];

		// Coefficient of restitution
		v_[0] = coeff_of_restitution_ * v_[0];
	}

	// [1번] 화면축소
	if ("버튼누르면"){
		//전체 사이즈 다줄어들기
	}else if("status=2 상태에서")

	// [2번] 마찰력
	if ( p_[1] == radius_ + room_->ground_height() ) {
		v_[0] *= frictional_force_;
	}


	// 속도 = 이전속도 + 시간(dt) * 가속도;
	v_[0] = v_[0] + dt * a[0];
	v_[1] = v_[1] + dt * a[1];
}
