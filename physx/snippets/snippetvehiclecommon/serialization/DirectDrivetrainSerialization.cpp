// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//  * Neither the name of NVIDIA CORPORATION nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
// OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Copyright (c) 2008-2025 NVIDIA Corporation. All rights reserved.
// Copyright (c) 2004-2008 AGEIA Technologies, Inc. All rights reserved.
// Copyright (c) 2001-2004 NovodeX AG. All rights reserved.  

#include "DirectDrivetrainSerialization.h"
#include "SerializationCommon.h"

#include <fstream>
#include <sstream>

namespace snippetvehicle
{

bool readThrottleResponseParams
(const rapidjson::Document& config, const PxVehicleAxleDescription& axleDesc,
	PxVehicleDirectDriveThrottleCommandResponseParams& throttleResponseParams)
{
	if (!config.HasMember("ThrottleCommandResponseParams"))
		return false;

	if (!readCommandResponseParams(config["ThrottleCommandResponseParams"], axleDesc, throttleResponseParams))
		return false;

	return true;
}

bool writeThrottleResponseParams
(const PxVehicleDirectDriveThrottleCommandResponseParams& throttleResponseParams, const PxVehicleAxleDescription& axleDesc,
 rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer)
{
	writer.Key("ThrottleCommandResponseParams");
	writer.StartObject();
	writeCommandResponseParams(throttleResponseParams, axleDesc, writer);
	writer.EndObject();
	return true;
}

bool readDirectDrivetrainParamsFromJsonFile(const char* directory, const char* filename,
	const PxVehicleAxleDescription& axleDescription, DirectDrivetrainParams& directDrivetrainParams)
{
	rapidjson::Document config;
	if (!openDocument(directory, filename, config))
		return false;

	if(!readThrottleResponseParams(config, axleDescription, directDrivetrainParams.directDriveThrottleResponseParams))
		return false;

	return true;
}

bool writeDirectDrivetrainParamsToJsonFile(const char* directory, const char* filename,
	const PxVehicleAxleDescription& axleDescription, const DirectDrivetrainParams& directDrivetrainParams)
{
	rapidjson::StringBuffer strbuf;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(strbuf);

	writer.StartObject();
	writeThrottleResponseParams(directDrivetrainParams.directDriveThrottleResponseParams, axleDescription, writer);
	writer.EndObject();

	std::ofstream myfile;
	myfile.open(std::string(directory) + "/" + filename);
	myfile << strbuf.GetString() << std::endl;
	myfile.close();

	return true;
}

}//namespace snippetvehicle
