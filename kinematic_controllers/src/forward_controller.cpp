#include <kinematic_controllers/forward_controller.h>
#include <../etc/pid.h>

ForwardController::ForwardController(ros::NodeHandle &handle, double update_frequency)
    :ControllerBase(handle, update_frequency)
    ,_kp("/controller/forward/kp", 0.15)
    ,_active(false)
    ,_velocity(0)
    ,_twist(new geometry_msgs::Twist)
{
    _sub_vel = _handle.subscribe("/controller/forward/velocity", 1, &ForwardController::callback_forward_velocity, this);
    _sub_act = _handle.subscribe("/controller/forward/active",   1, &ForwardController::callback_activate, this);
}

ForwardController::~ForwardController()
{}

void ForwardController::callback_forward_velocity(const std_msgs::Float64ConstPtr& vel) {
    _velocity = vel->data;
}

void ForwardController::callback_activate(const std_msgs::BoolConstPtr& val) {
    _active = val->data;
}

geometry_msgs::TwistConstPtr ForwardController::update()
{
    if (_active)
        _twist->linear.x += pd::P_control(_kp(), _twist->linear.x, _velocity);
    else
        _twist->linear.x += pd::P_control(_kp(), _twist->linear.x, 0);

    return _twist;
}

/*
//------------------------------------------------------------------------------
// Constants

const double PUBLISH_FREQUENCY = 10.0;
const double DEFAULT_VELOCITY = 0.5;

//------------------------------------------------------------------------------
// Member

double _velocity = DEFAULT_VELOCITY;
bool _active;

Parameter<double> _kp("/controller/forward/kp", 0.15);

//------------------------------------------------------------------------------
// Callbacks

void callback_forward_velocity(const std_msgs::Float64ConstPtr& vel) {
    _velocity = vel->data;
}

void callback_activate(const std_msgs::BoolConstPtr& val) {
    _active = val->data;
}

//------------------------------------------------------------------------------
// Entry point

int main(int argc, char **argv)
{
    ros::init(argc, argv, "forward_controller");

    ros::NodeHandle n;
    ros::Subscriber sub_vel = n.subscribe("/controller/forward/velocity", 1, callback_forward_velocity);
    ros::Subscriber sub_act = n.subscribe("/controller/forward/active",   1, callback_activate);
    ros::Publisher pub = n.advertise<geometry_msgs::Twist>("/controller/forward/twist", 1);

    ros::Rate loop_rate(PUBLISH_FREQUENCY);

    geometry_msgs::Twist twist;

    while (n.ok()) {

        if (_active)
            twist.linear.x += pd::P_control(_kp(), twist.linear.x, _velocity);
        else
            twist.linear.x += pd::P_control(_kp(), twist.linear.x, 0);

        pub.publish(twist);

        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}
*/
