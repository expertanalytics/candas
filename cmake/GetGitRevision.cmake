
# get the path of the current file
# - this must be done at include time, not function call time
get_filename_component(MODULE_PATH ${CMAKE_CURRENT_LIST_FILE} DIRECTORY)
set(MODULE_GRAB_IMPL_FILE "${MODULE_PATH}/GrabGitRev.cmake.in")
if(NOT EXISTS ${MODULE_GRAB_IMPL_FILE})
    message(FATAL_ERROR "Cannot determine implementation file.")
endif()

# ==========================================================================================
# Determine the revision of the previous commit.
#
# When run the function defines three variables:
# * GIT_REV_FOUND   :: A boolean which is TRUE if the revision was found.
# * GIT_REV_SHORT   :: The short seven character version of the revision.
# * GIT_REV_LONG    :: The full long revision.
#
# ==========================================================================================
function(get_git_revision root_path)

    set(GIT_REF_FOUND FALSE PARENT_SCOPE)
    set(GIT_REF_SHORT ""    PARENT_SCOPE)
    set(GIT_REF_LONG  ""    PARENT_SCOPE)

    # the path of the .git directory
    set(GIT_DIR "${root_path}/.git")

    # only continue if the .git directory exists and contains a HEAD file
    if((EXISTS ${GIT_DIR}) AND (EXISTS "${GIT_DIR}/HEAD"))
        # create a data directory if needed
        set(GIT_DATA_DIR "${candas_BINARY_DIR}/CMakeFiles/git-data")
        if(NOT EXISTS ${GIT_DATA_DIR})
            file(MAKE_DIRECTORY ${GIT_DATA_DIR})
        endif()

        # determine ref
        set(HEAD_FILE "${GIT_DATA_DIR}/head")
        set(CONFIGURED_IMPL_FILE "${GIT_DATA_DIR}/GrabGitRef.cmake")
        # -----
        configure_file("${GIT_DIR}/HEAD" ${HEAD_FILE} COPYONLY)
        configure_file(${MODULE_GRAB_IMPL_FILE} ${CONFIGURED_IMPL_FILE} @ONLY)

        include(${CONFIGURED_IMPL_FILE})

        string(STRIP "${HEAD_HASH}" HEAD_HASH)
        string(LENGTH "${HEAD_HASH}" HEAD_HASH_LENGTH)
        if((DEFINED HEAD_HASH) AND (${HEAD_HASH_LENGTH} GREATER 0))
            string(SUBSTRING "${HEAD_HASH}" 0 7 HEAD_HASH_SHORT)
            # cannot determine a reference
            set(GIT_REV_FOUND TRUE                 PARENT_SCOPE)
            set(GIT_REV_SHORT "${HEAD_HASH_SHORT}" PARENT_SCOPE)
            set(GIT_REV_LONG  "${HEAD_HASH}"       PARENT_SCOPE)
        endif()
    endif()
endfunction()

