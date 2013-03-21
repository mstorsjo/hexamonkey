//This file is part of the HexaMonkey project, a multimedia analyser
//Copyright (C) 2013  Sevan Drapeau-Martin, Nicolas Fleury

//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either version 2
//of the License, or (at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

#include "mp4sampleentryparser.h"

#include "module.h"

#include "defaulttypes.h"
#include "standardtypes.h"
#include "mp4types.h"

using namespace defaultTypes;
using namespace standardTypes;
using namespace mp4Types;

Mp4SampleEntryParser::Mp4SampleEntryParser(Object &object, const Module &module)
    : ContainerParser(object, module)
{
}

void Mp4SampleEntryParser::doParse()
{
    addVariable(array(int8, 6*8), "reserved");
    addVariable(uint16, "data_reference_index");
}

Mp4AudioSampleEntryParser::Mp4AudioSampleEntryParser(Object &object, const Module &module)
    :ContainerParser(object, module)
{
}

void Mp4AudioSampleEntryParser::doParse()
{
    addVariable(array(uint32, 2*32), "reserved");
    addVariable(uint16, "channelcount");
    addVariable(uint16, "samplesize");
    addVariable(uint16, "pre_defined");
    addVariable(uint16, "reserved");
    addVariable(uint32, "samplerate");
}

Mp4VisualSampleEntryParser::Mp4VisualSampleEntryParser(Object &object, const Module &module)
    : ContainerParser(object, module)
{
}

void Mp4VisualSampleEntryParser::doParse()
{
    addVariable(uint16, "pre_defined");
    addVariable(uint16, "reserved");
    addVariable(array(uint32, 3*32), "pre_defined");
    addVariable(uint16, "width");
    addVariable(uint16, "height");
    addVariable(fixed32, "horizresolution");
    addVariable(fixed32, "vertresolution");
    addVariable(uint32, "reserved");
    addVariable(uint16, "frame_count");
    addVariable(string(32), "compressorname");
    addVariable(uint16, "depth");
    addVariable(int16, "pre_defined");
    while(availableSize()>0)
    {
        Object* box = addVariable(Box());
        if(box->type().extendsDirectly(module().getTemplate("CleanApertureBox")()))
            box->setName("clap");
        if(box->type().extendsDirectly(module().getTemplate("PixelAspectRatioBox")()))
            box->setName("pasp");
    }
}


Mp4XMLMetaSampleEntryParser::Mp4XMLMetaSampleEntryParser(Object &object, const Module &module)
    : ContainerParser(object, module)
{
}

void Mp4XMLMetaSampleEntryParser::doParse()
{
    std::cerr<<"XMLMetaDataEntry: ambiguous definition"<<std::endl;
}


Mp4TextMetaSampleEntryParser::Mp4TextMetaSampleEntryParser(Object &object, const Module &module)
    : ContainerParser(object, module)
{
}

void Mp4TextMetaSampleEntryParser::doParse()
{
    std::cerr<<"TextMetaDataEntry: ambiguous definition"<<std::endl;
}


Mp4HintSampleEntryParser::Mp4HintSampleEntryParser(Object &object, const Module &module)
    : ContainerParser(object, module)
{
}

void Mp4HintSampleEntryParser::doParse()
{
    addVariable(data(), "data");
}