/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is CBash code.
 *
 * The Initial Developer of the Original Code is
 * Waruddar.
 * Portions created by the Initial Developer are Copyright (C) 2010
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

 /**
    @file CBash.h
    @brief This file declares the C API functions.

    @details This documentation was not written by the original developer, and so may be inaccurate. In particular, cb_GetRecordHistory() and cb_IsRecordsFormIDsInvalid() may be documented incorrectly.
*/

#pragma once
// CBash.h
//#define _UNICODE
#include "CBashConfig.h"
#include "Types.h"


//Exported Functions
/**************************//**
    @name Version Functions
******************************/
///@{

/**
    @brief Get CBash's minor version number.
    @returns Cbash's major version number.
*/
DLLEXTERN uint32_t cb_GetVersionMajor();

/**
    @brief Get CBash's minor version number.
    @returns Cbash's major version number.
*/
DLLEXTERN uint32_t cb_GetVersionMinor();

/**
    @brief Get CBash's revision (patch) version number.
    @returns Cbash's revision (patch) version number.
*/
DLLEXTERN uint32_t cb_GetVersionRevision();

///@}
/**************************//**
    @name Logging action functions
******************************/
///@{

/**
    @brief Register a callback function for logging messages.
    @param _LoggingCallback A pointer to a callback function. If `NULL`, messages are printed to `stdout`. The callback function must take a message string argument, and returns the number of characters in the message, or `-1` if an error occurred.
*/
DLLEXTERN void cb_RedirectMessages(int32_t (*_LoggingCallback)(const char *));

/**
    @brief Register a callback function for tracing function calls.
    @details This function is called by many functions if they encounter an error, and is passed the name of the function it is called from. This makes it potentially useful for debugging purposes.
    @param _RaiseCallback A pointer to a function that takes a string argument and returns nothing. If `NULL`, no function call tracing occurs.
*/
DLLEXTERN void cb_AllowRaising(void (*_RaiseCallback)(const char *));

///@}
/**************************//**
    @name Collection action functions
******************************/
///@{

/**
    @brief Create a plugin collection.
    @details Collections are used to manage groups of mod plugins and their data in CBash.
    @param ModsPath Specifies the path to the folder containing the mod plugins that are to be added to the collection.
    @param CollectionType Specifies the type of game the collection is for.
    @returns A pointer to the newly-created cb_collection_t object.
*/
DLLEXTERN cb_collection_t * cb_CreateCollection(char * const ModsPath, const cb_game_type_t CollectionType);

/**
    @brief Delete a plugin collection.
    @details Deleting a collection frees all associated memory, invalidating associated pointers.
    @param CollectionID A pointer to the collection to be deleted.
    @returns `0` on success, `-1` if an error occurred.
*/
DLLEXTERN int32_t cb_DeleteCollection(cb_collection_t *CollectionID);

/**
    @brief Loads a collection of plugins.
    @details Loads the records from the plugins in the given collection into memory, where their data can be accessed.
    @param CollectionID A pointer to the collection to load.
    @param _ProgressCallback A pointer to a function to use as a progress callback. If `NULL`, no progress is reported. The function arguments are the load order position of the plugin currently being loaded, the maximum load order position, and the plugin filename. The function returns a boolean that is currently ignored, but may in future be used to signal cancellation of loading by the client.
    @returns `0` on success, `-1` if an error occurred.
*/
DLLEXTERN int32_t cb_LoadCollection(cb_collection_t *CollectionID, bool (*_ProgressCallback)(const uint32_t, const uint32_t, const char *));

/**
    @brief Unloads a collection of plugins.
    @details Unloads any records from the plugins in the given collection that have previously been loaded into memory, without deleting the collection.
    @param CollectionID A pointer to the collection to unload.
    @returns `0` on success, `-1` if an error occurred.
*/
DLLEXTERN int32_t cb_UnloadCollection(cb_collection_t *CollectionID);

/**
    @brief Get the game type a collection was created for.
    @param CollectionID The collection to get the game type for.
    @returns The collection game type.
*/
DLLEXTERN int32_t cb_GetCollectionType(cb_collection_t *CollectionID);

/**
    @brief Unload all collections of plugins that have been created by CBash.
    @details Unloads all loaded collections from memory, without deleting them. Has the same effect as calling cb_UnloadCollection() for each collection that has been created.
    @returns `0` on success, `-1` if an error occurred.
*/
DLLEXTERN int32_t cb_UnloadAllCollections();

/**
    @brief Delete all plugin collections created by CBash.
    @details Has the same effect as calling cb_UnloadCollection() for each collection that has been created.
    @returns `0` on success, `-1` if an error occurred.
*/
DLLEXTERN int32_t cb_DeleteAllCollections();

///@}
/**************************//**
    @name Mod action functions
******************************/
///@{

/**
    @brief Add a plugin to a collection.
    @param CollectionID The collection to add the plugin to.
    @param ModName The filename of the plugin to add.
    @param ModFlagsField Flags that determine how the plugin is loaded and what can be edited once it has been loaded.
    @returns A pointer to the plugin object added to the collection.
*/
DLLEXTERN cb_mod_t * cb_AddMod(cb_collection_t *CollectionID, char * const ModName, const cb_mod_flags_t ModFlagsField);

/**
    @brief Load a single plugin.
    @details Loads the records from the given plugin into memory.
    @param ModID A pointer to the plugin object to load.
    @returns `0` on success, `-1` if an error occurred.
*/
DLLEXTERN int32_t cb_LoadMod(cb_mod_t *ModID);

/**
    @brief Unload a single plugin.
    @details Unloads the records from the given plugin.
    @param ModID A pointer to the plugin object to unload.
    @returns `0` on success, `-1` if an error occurred.
*/
DLLEXTERN int32_t cb_UnloadMod(cb_mod_t *ModID);

/**
    @brief Remove unreferenced masters from a plugin.
    @details This function removes any entries in the given plugin's list of masters that aren't referenced in any of the plugin's records. Note that unreferenced masters are sometimes added to plugins to make explicit an otherwise implicit dependency.
    @param ModID A pointer to the plugin object for which unreferenced masters should be removed.
    @returns `0` on success, `-1` if an error occurred.
*/
DLLEXTERN int32_t cb_CleanModMasters(cb_mod_t *ModID);

/**
    @brief Save a single plugin's data to a plugin file.
    @param ModID A pointer to the plugin object to save.
    @param SaveFlagsField Flags that determine how the plugin is saved.
    @param DestinationName The output plugin filename.
    @returns `0` on success, `-1` if an error occurred.
*/
DLLEXTERN int32_t cb_SaveMod(cb_mod_t *ModID, const cb_save_flags_t SaveFlagsField, char * const DestinationName);

///@}
/**************************//**
    @name Mod info functions
******************************/
///@{

/**
    @brief Get the number of mods in a collection.
    @param CollectionID The collection to query.
    @returns The number of mods in the given collection, or `-1` if an error occurred.
*/
DLLEXTERN int32_t cb_GetAllNumMods(cb_collection_t *CollectionID);

/**
    @brief Get an array of plugin object pointers for the plugins in a collection.
    @param CollectionID The collection to query.
    @param ModIDs An array of plugin object pointers. The array passed to the function must be preallocated to the correct size, as given by cb_GetAllNumMods(). The array contents are filled by the function to point to the plugin objects within the collection queried.
    @returns `0` on success, `-1` if an error occurred.
*/
DLLEXTERN int32_t cb_GetAllModIDs(cb_collection_t *CollectionID, cb_mod_t ** ModIDs);

/**
    @brief Get the number of mods in a collection's load order.
    @details Returns the number of plugins that were added to the collection with the ::CB_IN_LOAD_ORDER flag.
    @param CollectionID The collection to query.
    @returns The number of mods in the given collection's load order, or `-1` if an error occurred.
*/
DLLEXTERN int32_t cb_GetLoadOrderNumMods(cb_collection_t *CollectionID);

/**
    @brief Get an array of plugin object pointers for the plugins in a collection's load order.
    @param CollectionID The collection to query.
    @param ModIDs An array of plugin object pointers. The array passed to the function must be preallocated to the correct size, as given by cb_GetLoadOrderNumMods(). The array contents are filled by the function to point to the plugin objects within the collection queried.
    @returns `0` on success, `-1` if an error occurred.
*/
DLLEXTERN int32_t cb_GetLoadOrderModIDs(cb_collection_t *CollectionID, cb_mod_t ** ModIDs);

/**
    @brief Get a plugin's filename from its object pointer.
    @details The filename will include the `.ghost` extension if the plugin is ghosted.
    @param ModID The object pointer of the plugin to look up.
    @returns The plugin's filename, or `NULL` if an error occurred.
*/
DLLEXTERN char * cb_GetFileNameByID(cb_mod_t *ModID);

/**
    @brief Get a plugin's filename from its position in the load order.
    @details The filename will include the `.ghost` extension if the plugin is ghosted.
    @param CollectionID The collection to query.
    @param ModIndex The load order position to look up.
    @returns The plugin's filename, or `NULL` if an error occurred.
*/
DLLEXTERN char * cb_GetFileNameByLoadOrder(cb_collection_t *CollectionID, const uint32_t ModIndex);

/**
    @brief Get a plugin's unghosted filename from its object pointer.
    @details Returns the same value as cb_GetFileNameByID() for unghosted plugins, and the filename minus the `.ghost` extension for ghosted plugins.
    @param ModID The object pointer of the plugin to look up.
    @returns The plugin's unghosted filename, or `NULL` if an error occurred.
*/
DLLEXTERN char * cb_GetModNameByID(cb_mod_t *ModID);

/**
    @brief Get a plugin's unghosted filename from its position in the load order.
    @details Returns the same value as cb_GetFileNameByLoadOrder() for unghosted plugins, and the filename minus the `.ghost` extension for ghosted plugins.
    @param CollectionID The collection to query.
    @param ModIndex The load order position to look up, or `NULL` if an error occurred.
    @returns The plugin's unghosted filename, or `NULL` if an error occurred.
*/
DLLEXTERN char * cb_GetModNameByLoadOrder(cb_collection_t *CollectionID, const uint32_t ModIndex);

/**
    @brief Get a plugin's object using its filename.
    @param CollectionID The collection to query.
    @param ModName The plugin filename.
    @returns A pointer to the plugin object, or `NULL` if the plugin was not found.
*/
DLLEXTERN cb_mod_t * cb_GetModIDByName(cb_collection_t *CollectionID, char * const ModName);

/**
    @brief Get a plugin's object using its position in the load order.
    @param CollectionID The collection to query.
    @param ModIndex The load order position to look up.
    @returns A pointer to the plugin object, or `NULL` if the plugin was not found.
*/
DLLEXTERN cb_mod_t * cb_GetModIDByLoadOrder(cb_collection_t *CollectionID, const uint32_t ModIndex);

/**
    @brief Get a plugin's load order position using its filename.
    @param CollectionID The collection to query.
    @param ModName The plugin filename to look up.
    @returns The plugin's load order position, or `-1` if an error occurred.
*/
DLLEXTERN int32_t cb_GetModLoadOrderByName(cb_collection_t *CollectionID, char * const ModName);

/**
    @brief Get a plugin's load order position using its object pointer.
    @param ModID The plugin's object pointer.
    @returns The plugin's load order position, or `-1` if an error occurred.
*/
DLLEXTERN int32_t cb_GetModLoadOrderByID(cb_mod_t *ModID);

/**
    @brief Get a plugin using a record from it.
    @param RecordID The record to get the parent plugin of.
    @returns A plugin pointer, or `NULL` if an error occurred.
*/
DLLEXTERN cb_mod_t * cb_GetModIDByRecordID(cb_record_t *RecordID);

/**
    @brief Get a collection using a record from a plugin in it.
    @param RecordID The record to get the parent plugin's collection from.
    @returns A collection pointer, or `NULL` if an error occurred.
*/
DLLEXTERN cb_collection_t * cb_GetCollectionIDByRecordID(cb_record_t *RecordID);

/**
    @brief Get a collection using a plugin in it.
    @param ModID The plugin to get the parent collection of.
    @returns A collection pointer, or `NULL` if an error occurred.
*/
DLLEXTERN cb_collection_t * cb_GetCollectionIDByModID(cb_mod_t *ModID);

/**
    @brief Check if a plugin contains any records.
    @param ModID The plugin to query.
    @returns `1` if the plugin is empty, `0` otherwise.
*/
DLLEXTERN uint32_t cb_IsModEmpty(cb_mod_t *ModID);

/**
    @brief Get the number of different record types in a plugin.
    @details This function will fail unless the plugin was added to the collection with the ::CB_TRACK_NEW_TYPES flag.
    @param ModID The plugin to query.
    @returns The number of record types in the plugin, or `-1` if an error occurred.
*/
DLLEXTERN int32_t cb_GetModNumTypes(cb_mod_t *ModID);

/**
    @brief Get an array of different record types in a plugin.
    @details This function will fail unless the plugin was added to the collection with the ::CB_TRACK_NEW_TYPES flag.
    @param ModID The plugin to query.
    @param RecordTypes An array of record IDs. Each ID is a four-character sequence in in reverse, eg. `TES4` is stored as `4SET`. The array passed to the function must be preallocated to the correct size, as given by cb_GetModNumTypes(). The array contents are filled by the function.
    @returns `0` on success, `-1` if an error occurred.
*/
DLLEXTERN int32_t cb_GetModTypes(cb_mod_t *ModID, uint32_t * RecordTypes);

/**
    @brief Get the number of empty record groups in a plugin.
    @param ModID The plugin to query.
    @returns The number of empty record groups in the plugin, or `-1` if an error occurred.
*/
DLLEXTERN int32_t cb_GetModNumEmptyGRUPs(cb_mod_t *ModID);

/**
    @brief Get the number of orphaned records in a plugin.
    @details Orphaned records are those which reference a parent record that does not exist.
    @param ModID The plugin to query.
    @returns The number of orphaned records in the plugin, or `-1` if an error occurred.
*/
DLLEXTERN int32_t cb_GetModNumOrphans(cb_mod_t *ModID);

/**
    @brief Get an array of orphaned record FormIDs in a plugin.
    @details Orphaned records are those which reference a parent record that does not exist.
    @param ModID The plugin to query.
    @param FormIDs An outputted array of the FormIDs of the orphaned records in the plugin. The array passed to the function must be preallocated to the correct size, as given by cb_GetModNumOrphans(). The array contents are filled by the function.
    @returns `0` on success, `-1` if an error occurred.
*/
DLLEXTERN int32_t cb_GetModOrphansFormIDs(cb_mod_t *ModID, cb_formid_t * FormIDs);

///@}
/**************************//**
    @name FormID functions
******************************/
///@{

/**
    @brief Get the long-format FormID for a record.
    @details Long-format FormIDs convert the mod index stored in the first byte of a FormID into a plugin filename string, for unambiguous referencing independent of load order.
    @param RecordID The record to query.
    @param FormID The FormID to get the plugin filename referenced in its mod index byte.
    @param IsMGEFCode Whether or not the FormID passed is a MGEF code. MGEF (Magic Effect) records are special cases that are referenced using their EditorIDs rather than their FormIDs, so need special handling.
    @returns The filename of the plugin referenced by the given FormID, or `NULL` if an error occurred.
*/
DLLEXTERN char * cb_GetLongIDName(cb_record_t *RecordID, const uint32_t FormID, const bool IsMGEFCode);

/**
    @brief Get a FormID for an object in a plugin.
    @details  A FormID is composed of a one-byte mod index, and a 3-byte ObjectID. This function combines the mod index of the given plugin with the given ObjectID to create a FormID.
    @param ModID The plugin to query.
    @param ObjectID An ObjectID to create a FormID from. The last 3 bytes of the given ObjectID will be used in the FormID produced.
    @param IsMGEFCode Whether or not the ObjectID passed is for a MGEF code. MGEF (Magic Effect) records are special cases that are referenced using their EditorIDs rather than their FormIDs, so need special handling.
    @returns The FormID produced, or `NULL` if an error occurred.
*/
DLLEXTERN uint32_t cb_MakeShortFormID(cb_mod_t *ModID, const uint32_t ObjectID, const bool IsMGEFCode);

///@}
/**************************//**
    @name Record action functions
******************************/
///@{

/**
    @brief Create a new record.
    @param ModID The plugin to create the record in.
    @param RecordType The record type.
    @param RecordFormID The record FormID.
    @param RecordEditorID The record EditorID.
    @param ParentID The parent record for the record to be created. Some record types, usually worldspace-related, have hierarchies of parent and child records. If no parent is desired, `NULL` can be passed.
    @param CreateFlags Flags that determine how the record is created.
    @returns A pointer to the created record, or `NULL` if an error was encountered.
*/
DLLEXTERN cb_record_t * cb_CreateRecord(cb_mod_t *ModID, const uint32_t RecordType, const cb_formid_t RecordFormID, char * const RecordEditorID, cb_record_t *ParentID, const cb_create_flags_t CreateFlags);

/**
    @brief Copy a record from one plugin into another.
    @param RecordID The record to be copied.
    @param DestModID The plugin to copy the record into.
    @param DestParentID The parent record for the record copy. Some record types, usually worldspace-related, have hierarchies of parent and child records. If no parent is desired, `NULL` can be passed.
    @param DestRecordFormID The FormID of the record copy.
    @param DestRecordEditorID The Editor ID of the record copy.
    @param CreateFlags Flags that determine how the record copy is created.
    @returns A pointer to the record copy, or `NULL` if an error was encountered.
*/
DLLEXTERN cb_record_t * cb_CopyRecord(cb_record_t *RecordID, cb_mod_t *DestModID, cb_record_t *DestParentID, const cb_formid_t DestRecordFormID, char * const DestRecordEditorID, const cb_create_flags_t CreateFlags);

/**
    @brief Unload a record from memory.
    @details If the record has been changed and the changes are unsaved, it will remain in memory.
    @param RecordID The record to unload.
    @returns `1` on success, `0` on failure.
*/
DLLEXTERN int32_t cb_UnloadRecord(cb_record_t *RecordID);

/**
    @brief Discards changes made to a record since it was last saved.
    @details If no changes are present, the function return as if it failed.
    @param RecordID The record to reset.
    @returns `1` on success, `0` on failure.
*/
DLLEXTERN int32_t cb_ResetRecord(cb_record_t *RecordID);

/**
    @brief Delete a record.
    @param RecordID The record to delete.
    @returns `1` on success, `0` on failure.
*/
DLLEXTERN int32_t cb_DeleteRecord(cb_record_t *RecordID);

///@}
/**************************//**
    @name Record info functions
******************************/
///@{

/**
    @brief Get a record from a plugin using its FormID or EditorID.
    @param ModID The plugin to look in.
    @param RecordFormID The FormID to look for. If `NULL`, the EditorID value is used.
    @param RecordEditorID The EditorID to look for, used if the FormID given is `NULL`. If this is also `NULL`, the plugin's TES4 record is returned.
    @returns The specified record, or `NULL` if an error occurred.
*/
DLLEXTERN cb_record_t * cb_GetRecordID(cb_mod_t *ModID, const cb_formid_t RecordFormID, char * const RecordEditorID);

/**
    @brief Get the number of records of a specified type in a plugin.
    @param ModID The plugin to query.
    @param RecordType The record type to look for. This should be its 4-byte name in reverse order, eg. to search for `CELL` records, you would pass `'LLEC'`.
    @returns The number of records of the specified type, or `-1` if an error occurred.
*/
DLLEXTERN int32_t cb_GetNumRecords(cb_mod_t *ModID, const uint32_t RecordType);

/**
    @brief Get an array of records of a specified type in a plugin.
    @param ModID The plugin to query.
    @param RecordType The record type to look for. This should be its 4-byte name in reverse order, eg. to search for `CELL` records, you would pass a `uint32_t RecordType = 'LLEC';`.
    @param RecordIDs An array of record pointers, pre-allocated to be of the size given by cb_GetNumRecords(). This function populates the array.
    @returns The number of records retrieved, or `-1` if an error occurred.
*/
DLLEXTERN int32_t cb_GetRecordIDs(cb_mod_t *ModID, const uint32_t RecordType, cb_record_t ** RecordIDs);

/**
    @brief Check if the given record is winning any conflict with other records.
    @details A record wins a conflict if it is the last-loaded version of that record in the load order.
    @param RecordID The record to query.
    @param GetExtendedConflicts If true, checks for conflicts in plugins loaded with the ::CB_EXTENDED_CONFLICTS flag, otherwise they are ignored.
    @returns `1` if the record is winning, `0` if it is not, and `-1` if an error occurred.
*/
DLLEXTERN int32_t cb_IsRecordWinning(cb_record_t *RecordID, const bool GetExtendedConflicts);

/**
    @brief Get the number of conflicting versions of the given record in its parent collection.
    @param RecordID The record to look for conflicts for.
    @param GetExtendedConflicts If true, checks for conflicts in plugins loaded with the ::CB_EXTENDED_CONFLICTS flag, otherwise they are ignored.
    @returns The number of conflicting versions of the record, or `-1` if an error occurred.
*/
DLLEXTERN int32_t cb_GetNumRecordConflicts(cb_record_t *RecordID, const bool GetExtendedConflicts);

/**
    @brief Get an array of the different versions of the given record in its parent collection.
    @param RecordID The record to look for conflicts for.
    @param RecordIDs An array of record pointers, pre-allocated to be of the size given by cb_GetNumRecordConflicts(). This function populates the array.
    @param GetExtendedConflicts If true, checks for conflicts in plugins loaded with the ::CB_EXTENDED_CONFLICTS flag, otherwise they are ignored.
    @returns The number of records retrieved, or `-1` if an error occurred.
*/
DLLEXTERN int32_t cb_GetRecordConflicts(cb_record_t *RecordID, cb_record_t ** RecordIDs, const bool GetExtendedConflicts);

/**
    @brief Get an array of the different versions of the given record in its parent collection.
    @details Unlike cb_GetRecordConflicts(), this function will fail if the given record's parent plugin was loaded with the ::CB_EXTENDED_CONFLICTS flag set, and doesn't include the record passed in the outputted array.
    @param RecordID The record to look for conflicts for.
    @param RecordIDs An array of record pointers, pre-allocated to be of the size given by cb_GetNumRecordConflicts(). This function populates the array.
    @returns The number of records retrieved, or `-1` if an error occurred.
*/
DLLEXTERN int32_t cb_GetRecordHistory(cb_record_t *RecordID, cb_record_t ** RecordIDs);

/**
    @brief Get the number of Identical To Master records in a plugin.
    @details Identical To Master records are unedited copies of records present in a plugin's masters.
    @param ModID The plugin to query.
    @returns The number of Identical To Master records, or `-1` if an error occurred.
*/
DLLEXTERN int32_t cb_GetNumIdenticalToMasterRecords(cb_mod_t *ModID);

/**
    @brief Gets an array of the Identical To Master records in a plugin.
    @details Identical To Master records are unedited copies of records present in a plugin's masters.
    @param ModID The plugin to query.
    @param RecordIDs An array of record pointers, pre-allocated to be of the size given by cb_GetNumIdenticalToMasterRecords(). This function populates the array.
    @returns The number of records the array is populated with, or `-1` if an error occurred.
*/
DLLEXTERN int32_t cb_GetIdenticalToMasterRecords(cb_mod_t *ModID, cb_record_t ** RecordIDs);

/**
    @brief Check if a record's FormID or any of the FormIDs referenced by the record are invalid.
    @param RecordID The record to check.
    @returns `1` if the record has or references an invalid FormID, `0` if all the FormIDs it contains are valid, or `-1` if an error occurred.
*/
DLLEXTERN int32_t cb_IsRecordFormIDsInvalid(cb_record_t *RecordID);

///@}
/**************************//**
    @name Mod or Record action functions
******************************/
///@{

/**
    @brief Update FormID references in a given plugin or record.
    @param ModID The plugin to operate on. If `NULL`, RecordID must be non-`NULL`.
    @param RecordID The record to operate on. If `NULL`, references in all the records in the given plugin will be updated.
    @param OldFormIDs An input array of the FormIDs to update.
    @param NewFormIDs An input array of the new FormIDs that correspond to the FormIDs in OldFormIDs.
    @param Changes An output array of the number of changes made for each FormID that was inputted.
    @param ArraySize The size of the OldFormIDs, NewFormIDs and Changes arrays.
    @returns The total number of updated references, or `-1` if an error occurred.
*/
DLLEXTERN int32_t cb_UpdateReferences(cb_mod_t *ModID, cb_record_t *RecordID, cb_formid_t * OldFormIDs, cb_formid_t * NewFormIDs, uint32_t * Changes, const uint32_t ArraySize);

///@}
/**************************//**
    @name Mod or Record info functions
******************************/
///@{

/**
    @brief Check if a record has had its references updated.
    @param CollectionID The collection to query.
    @param RecordID The record to query. If `NULL`, all record changes in the collection are discarded.
    @returns `1` if the record has had its references updated, `0` if not, and `-1` if an error occurred.
*/
DLLEXTERN int32_t cb_GetRecordUpdatedReferences(cb_collection_t *CollectionID, cb_record_t *RecordID);

///@}
/**************************//**
    @name Field action functions
******************************/
///@{

/**
    @brief Set the FormID and EditorID of a record.
    @param RecordID The record to operate on.
    @param FormID The FormID to set. If `NULL`, the function will exit with error.
    @param EditorID The EditorID to set. If the EditorID is already in use by another record in the same plugin, the function will exit with error.
    @returns `1` if the FormID and/or EditorID was changed, or `-1` if nothing was changed or an error occurred.
*/
DLLEXTERN int32_t cb_SetIDFields(cb_record_t *RecordID, const cb_formid_t FormID, char * const EditorID);

/**
    @brief Set a record field's value.
    @details The parameters \p FieldID, \p ListIndex, \p ListFieldID, \p ListX2Index, \p ListX2FieldID, \p ListX3Index and \p ListX3FieldID take values that vary on a per-record and per-field level. To determine valid values for a particular record field, read the comments in the corresponding functions for the record's `*RecordAPI.cpp` file.
    @param RecordID The record in which the field is found.
    @param FieldID
    @param ListIndex
    @param ListFieldID
    @param ListX2Index
    @param ListX2FieldID
    @param ListX3Index
    @param ListX3FieldID
    @param FieldValue The value to set. Any memory allocated for the data passed can be freed once the function has completed, as CBash makes a copy of the data.
    @param ArraySize The length of the data to be set as the field's value.
    @returns
*/
DLLEXTERN void cb_SetField(cb_record_t *RecordID, FIELD_IDENTIFIERS, void *FieldValue, const uint32_t ArraySize);

/**
    @brief Delete a field from a record.
    @details The parameters \p FieldID, \p ListIndex, \p ListFieldID, \p ListX2Index, \p ListX2FieldID, \p ListX3Index and \p ListX3FieldID take values that vary on a per-record and per-field level. To determine valid values for a particular record field, read the comments in the corresponding functions for the record's `*RecordAPI.cpp` file.
    @param RecordID The record in which the field is found.
    @param FieldID
    @param ListIndex
    @param ListFieldID
    @param ListX2Index
    @param ListX2FieldID
    @param ListX3Index
    @param ListX3FieldID
*/
DLLEXTERN void cb_DeleteField(cb_record_t *RecordID, FIELD_IDENTIFIERS);

///@}
/**************************//**
    @name Field info functions
******************************/
///@{

/**
    @brief Get the type of a field's value.
    @details The parameters \p FieldID, \p ListIndex, \p ListFieldID, \p ListX2Index, \p ListX2FieldID, \p ListX3Index, \p ListX3FieldID and \p WhichAttribute take values that vary on a per-record and per-field level. To determine valid values for a particular record field, read the comments in the corresponding functions for the record's `*RecordAPI.cpp` file.
    @param RecordID The record in which the field is found.
    @param FieldID
    @param ListIndex
    @param ListFieldID
    @param ListX2Index
    @param ListX2FieldID
    @param ListX3Index
    @param ListX3FieldID
    @param WhichAttribute For fields that consist of more than one attribute value, this specifies which attribute to get. For single-attribute fields, it is ignored.
    @returns A ::cb_field_type_t value.
*/
DLLEXTERN uint32_t cb_GetFieldAttribute(cb_record_t *RecordID, FIELD_IDENTIFIERS, const uint32_t WhichAttribute);

/**
    @brief Get a field's value.
    @details The parameters \p FieldID, \p ListIndex, \p ListFieldID, \p ListX2Index, \p ListX2FieldID, \p ListX3Index and \p ListX3FieldID take values that vary on a per-record and per-field level. To determine valid values for a particular record field, read the comments in the corresponding functions for the record's `*RecordAPI.cpp` file.
    @param RecordID The record in which the field is found.
    @param FieldID
    @param ListIndex
    @param ListFieldID
    @param ListX2Index
    @param ListX2FieldID
    @param ListX3Index
    @param ListX3FieldID
    @param FieldValues
    @returns
*/
DLLEXTERN void * cb_GetField(cb_record_t *RecordID, FIELD_IDENTIFIERS, void **FieldValues);

///@}
