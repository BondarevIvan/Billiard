from jinja2 import Template
from sys import argv
import os


class Settings:
    def __init__(self, settings_folder):
        self.settings_folder = settings_folder
        self.subdirectory_cmake_pattern = f'{settings_folder}/PatternSubdirectoryCMakeLists.txt'
        self.main_cmake_pattern = f'{settings_folder}/PatternMainCMakeLists.txt'
        self.cmake_list_name = 'CMakeLists.txt'
        self.deffault_creater_name = 'bonka.make'


def fill_file(filename, pattern):
    filein = open(filename, 'r')
    src = Template( filein.read() )
    return src.render(pattern)


def create_dirs(list_dirs : list):
    try:
        os.mkdir('/'.join(list_dirs))
    except:
        pass


def create_file(name, text):
    if '/' in name:
        create_dirs(name.split('/')[:-1])        
    file = open(name, 'w')
    file.write(text)
    file.close()


def condensation_graph(graph : dict):
    order = []
    used = set()
    def dfs(vertex):
        used.add(vertex)
        for to in graph.get(vertex, []):
            if not to in used:
                dfs(to)
        order.append(vertex)
    for vertex in graph.keys():
        if not vertex in used:
            dfs(vertex)
    return order[::-1]


def ordered_subdirectories(filename):
    bonkafile = open(filename, 'r')
    lines = [el for el in bonkafile.read().split('\n')\
                      if el != '']
    graph = {}
    for line in lines:
        if ':' in line:
            subdir, sons = line.split(':')
            graph[subdir] = [el for el in sons.split(' ') if el != '']
    return condensation_graph(graph)

# filename - file with subdirectories
def autocreater(filename, settings : Settings):
    subdirectories = ordered_subdirectories(filename)
    create_file(settings.cmake_list_name,
                fill_file(settings.main_cmake_pattern,
                {
                    'LIST_DIRECTORY': ' '.join(subdirectories)
                }))
    for subdirectory in subdirectories:
        create_file(f'{subdirectory}/{settings.cmake_list_name}',
            fill_file(settings.subdirectory_cmake_pattern,
            {
                'NAME_SUBPROJECT': subdirectory
            }))


if __name__ == '__main__':
    setting_folder = '.'
    setting_folder = '/'.join(argv[0].split('/')[:-1])
    settings = Settings(setting_folder)
    settings_file = settings.deffault_creater_name
    if len(argv) > 1:
        settings_file = argv[1]
    autocreater(settings_file, settings)
