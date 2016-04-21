defineTest(copyLibrary) {
    #get param
    folder = $$1
    library = $$2
    destination = $$3

    #add correct extension to the lib
    win32 { library = $${library}.dll }
    else:mac {
        library1 = lib$${library}.dylib
        library2 = lib$${library}.1.dylib
        library3 = lib$${library}.1.0.dylib
        library4 = lib$${library}.1.0.0.dylib
    }
    else:unix { library = library$${library}.so }
    else {library = library$${library}.$${QMAKE_EXTENSION_SHLIB}}

    mac {
        path1 = $$folder/$$library1
        path2 = $$folder/$$library2
        path3 = $$folder/$$library3
        path4 = $$folder/$$library4

        QMAKE_POST_LINK += $(COPY_FILE) \
                    $$system_quote($$shell_path($$path1)) \
                    $$system_quote($$shell_path($$destination)) $$escape_expand(\\n\\t)

        QMAKE_POST_LINK += $(COPY_FILE) \
                    $$system_quote($$shell_path($$path2)) \
                    $$system_quote($$shell_path($$destination)) $$escape_expand(\\n\\t)

        QMAKE_POST_LINK += $(COPY_FILE) \
                    $$system_quote($$shell_path($$path3)) \
                    $$system_quote($$shell_path($$destination)) $$escape_expand(\\n\\t)

        QMAKE_POST_LINK += $(COPY_FILE) \
                    $$system_quote($$shell_path($$path4)) \
                    $$system_quote($$shell_path($$destination)) $$escape_expand(\\n\\t)
    }
    else {

        path = $$folder/$$library

        QMAKE_POST_LINK += $(COPY_FILE) \
                    $$system_quote($$shell_path($$path)) \
                    $$system_quote($$shell_path($$destination)) $$escape_expand(\\n\\t)
    }

    export(QMAKE_POST_LINK)
}
