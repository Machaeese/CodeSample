subdir('ActorGraph')


#executable for pathfinder
pathfinder_exe = executable('pathfinder.cpp.executable',
    sources:['pathfinder.cpp'],
    dependencies : [actor_graph_dep],
    install : true)

#executable for linkpredictor
linkpredictor_exe = executable('linkpredictor.cpp.executable',
    sources:['linkpredictor.cpp'],
    dependencies : [actor_graph_dep],
    install : true)

#executable for movietraveler
movietraveler_exe = executable('movietraveler.cpp.executable',
    sources:['movietraveler.cpp'],
    dependencies : [actor_graph_dep],
    install : true)