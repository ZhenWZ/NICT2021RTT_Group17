

# Asistente de Detección de Máscaras / Mask Detection Assistant

| Versión | Fecha      | Descripción                                                  | Otro       |
| ------- | ---------- | ------------------------------------------------------------ | ---------- |
| v1.0.0  | 2021/07/22 | Modelo de detección de máscaras implementado en ART-Pi         |            |

## 1. Descripción del Proyecto / Introduction

Este proyecto implementa el modelo de detección de máscaras en la placa de desarrollo ART-Pi proporcionada por RT-Thread, lee los datos de imagen a través de gc0328 y, finalmente, muestra los resultados mediante la placa de expansión multimedia.

En este proyecto, entrenamos un modelo de detección de máscaras y lo implementamos en la placa de desarrollo ART-Pi. La placa de desarrollo recibe las imágenes capturadas por el módulo de cámara gc0328 y muestra el resultado del modelo de detección de máscaras en una pantalla integrada. 

## 2. Entorno / Environment

- Sistema operativo: Windows 10
- X-CUBE-AI: 5.2.0
- RT-Thread Studio: 2.1.1
- RT-AK

    [Repositorio de RT-AK](https://github.com/RT-Thread/RT-AK)
    
## 3. Componentes / Components

- ART-Pi
- Placa de expansión multimedia ART-Pi
- gc0328

## 4. Pasos / Steps

### 4.0 Preparación de Archivos

- Proyecto RT-Thread
- RT-AK
- Modelo preparado
- X-CUBE-AI

### 4.1 Implementación del Modelo / Deployment

En la línea de comandos, navegue hasta `RT-AK\rt_ai_tools` y ejecute

```
python aitools.py --project="工程路径" --model="模型路径" --model_name="mask" --platform=stm32 --ext_tools="X-CUBE-AI路径" --clear
```

Por ejemplo:

```
D:\RT-ThreadAI\RT-AK\rt_ai_tools>python aitools.py --project=D:\RT-ThreadAI\mask_detect --model=D:\RT-ThreadAI\RT-AK\rt_ai_tools\Models\mask_detect.tflite --model_name=mask --platform=stm32 --ext_tools=D:\RT-ThreadAI\stm32ai-windows-5.2.0\windows --clear
```

## 5. Entrenamiento del Modelo / Training

### 5.1 Entorno / Environment

- tensorflow==2.4.0
- opencv-python==4.5.1
- matplotlib==3.3.3

### 5.2 Conjuntos de Datos / Datasets

- Face Mask Lite Dataset, <https://www.kaggle.com/prasoonkottarathil/face-mask-lite-dataset>
- COVID Face Mask Detection Dataset, <https://www.kaggle.com/prithwirajmitra/covid-face-mask-detection-dataset>
- With/Without Mask, <https://www.kaggle.com/niharika41298/withwithout-mask>
- Face Mask Detection, <https://www.kaggle.com/andrewmvd/face-mask-detection>
- Face Mask Detection ~12K Images Dataset, <https://www.kaggle.com/ashishjangra27/face-mask-12k-images-dataset>

### 5.3 Estructura de la Red / Model Structure

- Dos capas convolucionales + una capa totalmente conectada

![model](https://user-images.githubusercontent.com/48997918/126664710-692b93d4-696b-4bf1-98d8-d134d9d4f42c.png)


### 5.4 Entrenamiento y Validación del Modelo / Traning & Validating

- Entrenamiento del Modelo / Training

![training](https://user-images.githubusercontent.com/48997918/126664723-b9e23965-ee89-411a-853a-e34bb0b62929.png)


- Precisión del Modelo Entrenado / Accuracy

![evaluate](https://user-images.githubusercontent.com/48997918/126664763-96c984d4-bd6e-4ced-9597-06ab6552f4ac.png)


## 6. Resultados de la Ejecución / Results

<img align="left" src=https://user-images.githubusercontent.com/48997918/126732799-459eb4a9-b067-45ee-ba04-f2875d0452c9.jpg width=200px/><img src=https://user-images.githubusercontent.com/48997918/126732808-3904e505-5377-47a5-af01-e26990329596.jpg width=200px/>


## Agradecimientos / Acknowledgements
- Derekduke
- lebhoryi
