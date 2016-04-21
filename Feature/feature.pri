defineTest(copyLibrary) {
    #get param
    folder = $$1
    library = $$2
    destination = $$3

    #add correct extension to the lib
    win32 { library = $${library}.dll }
    else:unix { library = library$${library}.so }
    else {library = library$${library}.$${QMAKE_EXTENSION_SHLIB}}

    path = $$folder/$$libaray


    QMAKE_POST_LINK += $(COPY_FILE) \
                    $$system_quote($$shell_path($$path)) \
                    $$system_quote($$shell_path($$destination)) $$escape_expand(\\n\\t)

    export(QMAKE_POST_LINK)

}
