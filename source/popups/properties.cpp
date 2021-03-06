#include "fs.h"
#include "gui.h"
#include "imgui.h"
#include "popups.h"
#include "utils.h"

namespace Popups {
    static char *FormatDate(char *string, time_t timestamp) {
		strftime(string, 36, "%Y/%m/%d %H:%M:%S", localtime(&timestamp));
		return string;
	}

	void PropertiesPopup(void) {
		Popups::SetupPopup("Properties");
		
		if (ImGui::BeginPopupModal("Properties", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
			std::string name_text = "Name: " + item.selected_filename;
			ImGui::Text(name_text.c_str());
			
			if (item.entries[item.selected].type == FsDirEntryType_File) {
				char size[16];
				Utils::GetSizeString(size, item.entries[item.selected].file_size);
				std::string size_text = "Size: ";
				size_text.append(size);
				ImGui::Text(size_text.c_str());
			}
			
			FsTimeStampRaw timestamp;
			if (R_SUCCEEDED(FS::GetTimeStamp(&item.entries[item.selected], &timestamp))) {
				if (timestamp.is_valid == 1) { // Confirm valid timestamp
					char date[3][36];
					
					std::string created_time = "Created: ";
					created_time.append(Popups::FormatDate(date[0], timestamp.created));
					ImGui::Text(created_time.c_str());
					
					std::string modified_time = "Modified: ";
					modified_time.append(Popups::FormatDate(date[1], timestamp.modified));
					ImGui::Text(modified_time.c_str());
					
					std::string accessed_time = "Accessed: ";
					accessed_time.append(Popups::FormatDate(date[2], timestamp.accessed));
					ImGui::Text(accessed_time.c_str());
				}
			}
			
			ImGui::Dummy(ImVec2(0.0f, 5.0f)); // Spacing
			
			if (ImGui::Button("OK", ImVec2(120, 0))) {
				ImGui::CloseCurrentPopup();
				item.state = MENU_STATE_OPTIONS;
			}

			ImGui::EndPopup();
		}

		ImGui::PopStyleVar();
	}
}
