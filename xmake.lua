add_requires('asio', 'sfml', 'gtest')

target("R-Type_client")
    set_kind("binary")
    set_languages('cxx17')
    add_includedirs("R-Type/Include/Client", "R-Type/Include/Client/Renderer", "R-Type/Include/Client/Audio",
    "R-Type/Include/Client/Ecs", "R-Type/Include/Client/Ecs/Systems", "R-Type/Include/Client/Ecs/Components",
    "R-Type/Include/Client/Ecs/Components/UI", "/R-Type/Include/Common", "R-Type/Include/Common/Ecs", 
    "R-Type/Include/Common/Ecs/Components", "R-Type/Include/Common/Ecs/Systems", "R-Type/Include/Common")
    add_files("R-Type/Src/Client/**.cpp", "R-Type/Src/Common/**.cpp")
    add_packages("asio", "sfml")

    after_build(function (target)
            print("Copying assets to build directory...")
            local binaryPath = "$(buildir)/$(plat)/$(arch)/$(mode)"
            os.mkdir(binaryPath .. "/assets")
            os.cp("assets/**",  binaryPath .. "/assets")
            print("Copying assets to build directory... Done !")
        end)

target("R-Type_server")
    set_kind("binary")
    set_languages('cxx17')
    add_includedirs("R-Type/Include/Server", "R-Type/Include/Server/Ecs/Components", "R-Type/Include/Server/Ecs/Systems",
    "R-Type/Include/Server/Network", "/R-Type/Include/Common", "R-Type/Include/Common/Ecs", 
    "R-Type/Include/Common/Ecs/Components", "R-Type/Include/Common/Ecs/Systems", "R-Type/Include/Common")
    add_files("R-Type/Src/Server/**.cpp", "R-Type/Src/Common/**.cpp")
    add_packages("asio")

target("R-Type_tests")
    set_kind("binary")
    set_languages('cxx17')
    add_includedirs("/R-Type/Include/Common", "R-Type/Include/Common/Ecs", 
    "R-Type/Include/Common/Ecs/Components", "R-Type/Include/Common/Ecs/Systems", "R-Type/Include/Common")
    add_files("R-Type/Tests/**.cpp", "R-Type/Src/Common/**.cpp")
    add_packages("gtest")