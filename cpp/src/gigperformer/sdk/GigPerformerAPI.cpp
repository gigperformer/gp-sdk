#include "gigperformer/sdk/GigPerformerFunctions.h"

#include <sstream>
#include <string>

#include "gigperformer/sdk/GPMidiMessages.h"
#include "gigperformer/sdk/GigPerformerAPI.h"

namespace gigperformer
{
namespace sdk
{

void GigPerformerAPI::Initialization()
{
}

void GigPerformerAPI::OnEditStateChanged(bool)
{
}

void GigPerformerAPI::OnModeChanged(int)
{
}

void GigPerformerAPI::OnSwitchToWiringView()
{
}

void GigPerformerAPI::OnSwitchToPanelView()
{
}

void GigPerformerAPI::OnTempoChanged(double)
{
}

void GigPerformerAPI::OnTunerModeChanged(bool)
{
}

void GigPerformerAPI::OnGlobalPlayStateChanged(double)
{
}

void GigPerformerAPI::OnWidgetValueChanged(const std::string &, double)
{
}

void GigPerformerAPI::OnWidgetStateChanged(const std::string &, int)
{
}

void GigPerformerAPI::OnWidgetCaptionChanged(const std::string &, const std::string &)
{
}

void GigPerformerAPI::OnMidiDeviceListChanged(std::vector<std::string> &, std::vector<std::string> &)
{
}

bool GigPerformerAPI::OnMidiIn(const std::string &, const uint8_t *, int)
{
    return false;
}

void GigPerformerAPI::OnStatusChanged(GPStatusType)
{
}

void GigPerformerAPI::OnSongChanged(int, int)
{
}

void GigPerformerAPI::OnSongPartChanged(int, int)
{
}

void GigPerformerAPI::OnSetlistChanged(const std::string &)
{
}

void GigPerformerAPI::OnRackspaceActivated()
{
}

void GigPerformerAPI::OnVariationChanged(int, int)
{
}

void GigPerformerAPI::OnOpen()
{
}

void GigPerformerAPI::OnClose()
{
}

int GigPerformerAPI::GetPanelCount()
{
    return 0;
}

std::string GigPerformerAPI::GetPanelName(int)
{
    return "";
}

std::string GigPerformerAPI::GetPanelXML(int)
{
    return "";
}

int GigPerformerAPI::GetMenuCount()
{
    return 0;
}

std::string GigPerformerAPI::GetMenuName(int)
{
    return "";
}

void GigPerformerAPI::InvokeMenu(int)
{
}

int GigPerformerAPI::RequestGPScriptFunctionSignatureList(GPScript_AllowedLocations,
                                                          ExternalAPI_GPScriptFunctionDefinition **)
{
    // By default, no GPScript functions defined so the count is 0
    return 0;
}

GigPerformerAPI::GigPerformerAPI(LibraryHandle handle) : GigPerformerFunctions(handle)
{
}

GigPerformerAPI::~GigPerformerAPI()
{
}

} // namespace sdk
  // namespace sdk
} // namespace gigperformer
  // namespace gigperformer
