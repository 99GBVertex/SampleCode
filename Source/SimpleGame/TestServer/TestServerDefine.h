#pragma once

enum ProtocolId : uint16
{
	None     = 0,

	QryHello = 4097, //(1 << 12 | 1) - System
	RplHello = 4098, //(1 << 12 | 2)

	QryGetInventory = 4099, //(1 << 12 | 3)
	RplGetInventory = 4100, //(1 << 12 | 4)
};

enum NetResultCode : uint16
{
	/// <summary>
	/// Success
	/// </summary>
	NoError = 0,
};