#pragma once

enum ProtocolId : uint16
{
	QryHello = 4097, //(1 << 12 | 1) - System
	RplHello = 4098, //(1 << 12 | 2)
};