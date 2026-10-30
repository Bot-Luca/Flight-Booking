# Flight Booking

Projeto final da matéria de programação em C: um sistema de agência de viagem em modo console, com cadastro de voos, passageiros e passagens.

## Baixar e executar

Não é necessário compilar nada. Baixe o pacote mais recente na página de [Releases](../../releases):

| Sistema | Arquivo | Como executar |
| --- | --- | --- |
| Windows | `flight-windows.zip` | Extraia o zip e dê duplo clique em `flight.exe` |
| Linux | `flight-linux.zip` | Extraia o zip e rode `./flight` no terminal |

> Os arquivos `.txt` (menu, despedida e texto filosófico) precisam ficar na mesma pasta do executável. Por isso eles são incluídos dentro dos zips.

## Compilar a partir do código

Requisitos: GCC e Make.

```bash
cd src
make
make run
```

Sem Make:

```bash
cd src
gcc -std=c11 -Wall -Wextra -o flight code.c
./flight
```

No Windows, o código detecta o sistema automaticamente, usa `cls` para limpar a tela e configura o terminal em UTF-8. O mesmo código-fonte compila em Linux e Windows.

## Estrutura do projeto

```text
src/
  code.c
  header.h
  menu.txt
  despedida.txt
  texto_filosofico.txt
  Makefile
.github/workflows/build.yml
```

## Funcionalidades

- Cadastro, alteração, exclusão e consulta de voos
- Painel de embarque
- Cadastro, alteração, exclusão e consulta de passageiros
- Emissão de passagens

## Integração contínua

O workflow do GitHub Actions compila o projeto a cada push e disponibiliza os pacotes `flight-windows.zip` e `flight-linux.zip` como artefatos. Ao criar uma tag `v*`, os mesmos pacotes são anexados automaticamente a um Release.

## Créditos

As artes ASCII foram feitas com o auxílio destes sites:

- Avião: [asciiart.website](https://asciiart.website/index.php?art=transportation/airplanes) — autor: Dick Williams, [rjw1@tyrell.net](mailto:rjw1@tyrell.net)
- Lettering: [patorjk.com/software/taag](https://patorjk.com/software/taag/#p=display&f=3D%20Diagonal&t=) — autor: -
