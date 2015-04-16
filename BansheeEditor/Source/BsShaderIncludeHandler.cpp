#include "BsShaderIncludeHandler.h"
#include "BsProjectLibrary.h"
#include "BsResources.h"
#include "BsProjectResourceMeta.h"
#include "BsBuiltinResources.h"
#include "BsBuiltinEditorResources.h"

namespace BansheeEngine
{
	HShaderInclude EditorShaderIncludeHandler::findInclude(const String& name) const
	{
		if (name.substr(0, 8) == "$ENGINE$")
		{
			if (name.size() > 8)
			{
				Path fullPath = BuiltinResources::DefaultShaderFolder;
				Path includePath = name.substr(9, name.size() - 9);

				fullPath.append(includePath);
				fullPath.setFilename(includePath.getFilename() + ".asset");

				return static_resource_cast<ShaderInclude>(Resources::instance().load(fullPath));
			}
		}
		else if (name.substr(0, 8) == "$EDITOR$")
		{
			if (name.size() > 8)
			{
				Path fullPath = BuiltinEditorResources::DefaultShaderFolder;
				Path includePath = name.substr(9, name.size() - 9);

				fullPath.append(includePath);
				fullPath.setFilename(includePath.getFilename() + ".asset");

				return static_resource_cast<ShaderInclude>(Resources::instance().load(fullPath));
			}
		}
		else
		{
			Path path = name;

			ProjectLibrary::LibraryEntry* entry = ProjectLibrary::instance().findEntry(path);
			if (entry != nullptr && entry->type == ProjectLibrary::LibraryEntryType::File)
			{
				ProjectLibrary::ResourceEntry* resEntry = static_cast<ProjectLibrary::ResourceEntry*>(entry);
				return static_resource_cast<ShaderInclude>(Resources::instance().loadFromUUID(resEntry->meta->getUUID()));
			}
		}

		return HShaderInclude();
	}
}