1. Para compilar utilize o comando "make all" do makefile, resultando no executável "run"

2. dentro da pasta jsonInput o arquivo scene deverá ter o seguinte formato

Um objeto chamado "camera", com vetores com os nomes: "origin", "horizontal", "vertical" e "corner"
Representando respectivamente a coordenada do(a):
	- A origem dos raios
	- A largura da tela onde serão projetados
	- A altura da tela onde serão projetados
	- O canto inferior esquerdo da tela onde serão projetados

{
    "camera":{
        "origin":[0.0,0.0,0.0],
        "horizontal":[4.0,0.0,0.0],
        "vertical":[0.0,2.0,0.0],
        "corner":[-2.0,-1.0,-1.0]
    }
}


3. Ao ser executado, o programa exibirá uma função sample que dará uma demonstração da projeção dos raios sobre uma esfera


4. A imagem resultante dessa projeção será salva em imageOutput