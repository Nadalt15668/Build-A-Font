import os
TEMPLATES_CHR_DIR = r".\Templates\CharacterTemplates\Characters"
TEMPLATES_NUM_DIR = r".\Templates\CharacterTemplates\Numbers"
TEMPLATES_SMBL_DIR = r".\Templates\CharacterTemplates\Symbols"

def retrieve_templates():
    filenames = os.listdir(TEMPLATES_CHR_DIR)
    filenames = filenames + os.listdir(TEMPLATES_NUM_DIR)
    filenames = filenames + os.listdir(TEMPLATES_SMBL_DIR)
    return filenames

def retrieve_clean_filenames():
    filenames = retrieve_templates()
    for i in range(len(filenames)):
        filenames[i] = filenames[i].replace(".png", "")
    return filenames