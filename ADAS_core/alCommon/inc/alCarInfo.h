
#pragma once

#include "mtype.h"

/**
*   \defgroup alCARINFO    alCarInfo
*   The module define the struct whiche inclues car runtime information, such like gear status, door opened/closed, .. etc.
*   Most of these information are provided by car sensor through CAN protocol.
*   There are some enum data are defined to incidate the status of gear, door, headlight, ....
*  @{
*/

/** \brief Define the flag for IGN status. */
typedef enum
{
    /** \brief Indicate the IGN status is on "OFF". */
    alCARINFO_IGN_OFF = 0,
    /** \brief Indicate the IGN status is on "ACCESSORY" : 僅提供車上附件的供電，例如音響. */
    alCARINFO_IGN_ACC = 1,
    /** \brief Indicate the IGN status is on "ON" : 車上完全上電 (引擎不見得已啟動). */
    alCARINFO_IGN_ON = 2,
    /** \brief Indicate the IGN status is on "START" : 發動引擎，回自動回 ON 的狀態. */
    alCARINFO_IGN_START = 3,
    /** \brief Indicate the IGN status is on "Invalid". */
    alCARINFO_IGN_INVALID = 7,

} alCARINFO_IGNStatus;

/** \brief Define the flag for gear status. */
typedef enum 
{
    /** \brief Indicate the gear status is on "P". */
    alCARINFO_GEAR_P = 0,
    /** \brief Indicate the gear status is on "R". */
    alCARINFO_GEAR_R = 1,
    /** \brief Indicate the gear status is on "N". */
    alCARINFO_GEAR_N = 2,
    /** \brief Indicate the gear status is on "D". */
    alCARINFO_GEAR_D = 3

} alCARINFO_GearStatus;

/** \brief Define the flag for door lock status. */
typedef enum 
{
    /** \brief Indicate the door is closed. */
    alCARINFO_DOOR_CLOSE = 0,
  
    /** \brief Indicate the door is opened. */
    alCARINFO_DOOR_OPEN = 1

} alCARINFO_DoorLock;

/** \brief Define the flag for wiper status. */
typedef enum 
{
    /** \brief Indicate the wiper is OFF. */
    alCARINFO_WIPER_OFF = 0,
  
    /** \brief Indicate the wiper is ON with lowest status. */
    alCARINFO_WIPER_INT = 1,

    /** \brief Indicate the wiper is ON with lower status. */
    alCARINFO_WIPER_LOW = 2,

    /** \brief Indicate the wiper is ON with higher status. */
    alCARINFO_WIPER_HIGH = 3,

    /** \brief Indicate the wiper is ON with mist status. */
    alCARINFO_WIPER_MIST = 4,

    /** \brief Indicate the wiper status is invalid. */
    alCARINFO_WIPER_INVALID = 7,

} alCARINFO_Wiper;

/** \brief Define the flag for brake status. */
typedef enum 
{
    /** \brief Indicate the brake is inactived. */
    alCARINFO_BRAKE_INACTIVE = 0,
  
    /** \brief Indicate the brake is actived. */
    alCARINFO_BRAKE_ACTIVE = 1

} alCARINFO_Brake;

/** \brief Define the flag for turn-light status. */
typedef enum
{
    /** \brief Indicate the turn light is "OFF". */
    alCARINFO_TURNLIGHT_OFF = 0,

    /** \brief Indicate the turn light is "ON". */
    alCARINFO_TURNLIGHT_ON = 1

} alCARINFO_TurnLight;

/** \brief Define the flag for head-light status. */
typedef enum 
{
    /** \brief Indicate the head light is "OFF". */
    alCARINFO_HEADLIGHT_OFF = 0,
  
    /** \brief Indicate the head light is "ON". */
    alCARINFO_HEADLIGHT_ON = 1

} alCARINFO_HeadLight;

/** \brief Define the flag for fog-light status. */
typedef enum 
{
    /** \brief Indicate the fog light is "OFF". */
    alCARINFO_FOGLIGHT_OFF = 0,
  
    /** \brief Indicate the fog light is "ON". */
    alCARINFO_FOGLIGHT_ON = 1

} alCARINFO_FogLight;

/** \brief Define the flag for tail-light status. */
typedef enum 
{
    /** \brief Indicate the tail light is "OFF". */
    alCARINFO_TAILLIGHT_OFF = 0,
  
    /** \brief Indicate the fog light is "ON". */
    alCARINFO_TAILLIGHT_ON = 1

} alCARINFO_TailLight;

/** \brief Define the flag for status of daytime running light . */
typedef enum
{
    /** \brief Indicate the day time running light is "OFF". */
    alCARINFO_DAYTIMERUNNINGLIGHT_OFF = 0,
  
    /** \brief Indicate the day time running light is "ON". */
    alCARINFO_DAYTIMERUNNINGLIGHT_ON = 1

} alCARINFO_DaytimeRunningLight;

/** \brief Define the structure for car data input. */
typedef struct
{
    /** \brief The time interval between current & previous frame. (in micro-sec) */
    UINT32  ulTimeInterval;

    /**
    \brief The IGN status of car. 
    \see alCARINFO_IGNStatus
    */
    alCARINFO_IGNStatus  ucIGN;

    /** 
    \brief The gear status of car. 
    \see alCARINFO_GearStatus
    */
    alCARINFO_GearStatus  ucGear;

    /** 
    \brief The left turning light status of car. On/Off 
    \see alCARINFO_TurnLight
    */
    alCARINFO_TurnLight  ucLeftTurnLight;

    /**
    \brief The right turning light status of car. On/Off 
    \see alCARINFO_TurnLight
    */
    alCARINFO_TurnLight  ucRightTurnLight;

    /** \brief Current Speed of the car. (in m/hr) */
    UINT32  ulSpeed;

    /** \brief The steering angle of the car. (in degree, started from 0 and need to be offset) */
    UINT32  ulSteeringAngle;

    /** 
    \brief The door lock status of the car. 
    \see alCARINFO_DoorLock
    */
    alCARINFO_DoorLock  ucDoorLock;

    /** 
    \brief The wiper status of the car.
    \see alCARINFO_DoorLock
    */
    alCARINFO_Wiper  ucWiper;

    /** \brief The yaw rate of the car. (in rad/sec ??) */
    UINT32  ulYawRate;

    /** 
    \brief The brake status of the car. 
    \see alCARINFO_Brake
    */
    alCARINFO_Brake  ucBrake;

    /** 
    \brief The Low head light status of the car. 
    \see alCARINFO_HeadLight
    */
    alCARINFO_HeadLight  ucLowHeadLight;

	/** 
    \brief The high head light status of the car.
    \see alCARINFO_HeadLight
    */
    alCARINFO_HeadLight  ucHighHeadLight;

    /** 
    \brief The front fog light status of the car. 
    \see alCARINFO_FogLight
    */
    alCARINFO_FogLight  ucFrontFogLight;

    /** 
    \brief The back fog light status of the car. 
    \see alCARINFO_FogLight
    */
    alCARINFO_FogLight  ucBackFogLight;

	/** 
    \brief The tail light status of the car.
    \see alCARINFO_TailLight
    */
    alCARINFO_TailLight ucTailLight;

	/** 
    \brief The daytime running light status of the car. 
    \see alCARINFO_DaytimeRunningLight
    */
    alCARINFO_DaytimeRunningLight ucDaytimeRunningLight;

} alCARINFO_Set;

/**
*   @}
*/
