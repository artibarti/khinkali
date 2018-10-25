#version 430

/** Első bemeneti objektumunk, a pozíció.
    Megjegyzés: a programban feltettük róla, hogy az indexe 0, 
    de mi ezt nem adtuk meg sehol a shaderben. A szabvány nem 
    garantálja, hogy ez feltétlenül 0 lesz, ez csak az implementáció 
    miatt működik egyelőre, viszont nem biztonságos erre támaszkodni. 
    Ennek megoldásáról következő laboron beszélünk. */
in vec3 vPos;

/** Második bemeneti objektumunk, a szín. Hasonló
    dolgok igazak rá is, mint az előző attribútumra. */
/** in vec3 vColor; */

/** Egyetlen kimeneti attribútumunk, amelyet a következő
    "shader stage", azaz a következő shader kap meg. */
/** out vec3 vColorVS; */

void main()
{
    /** Adjuk tovább egy az egyben a csúcshoz tartozó színt. A rendszer
        fogja lekezelni, hogy hogyan kell a csúcsokhoz tartozó színekből
        (attribútumokból) a konkrét pixelekhez tartozóakat előállítani. */
    /** vColorVS = vColor; */
    
    /** Írjuk ki a csúcshoz tartozó pozíció koordinátáit. Erre a GLSL
        beépített változóját kell használnunk. */
    gl_Position = vec4(vPos, 1);
}