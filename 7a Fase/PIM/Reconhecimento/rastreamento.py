import cv2
import sys, os

if len(sys.argv) < 2:
    print("Uso: python rastreamento.py nome_video.mp4 nome_objeto.png")
    exit()

video_filename = sys.argv[1]
pasta_video = "frames_" + video_filename
objeto_filename = sys.argv[2]

if os.path.isdir(pasta_video):
    print ("Diretório com frames já existe, passando para o rastreamento.")
else:
    print ("Diretório com frames inexistente, iniciando processo de separação de frames...")
    video = cv2.VideoCapture(video_filename)
    ha_frames, frame = video.read()
    count = 0
    os.mkdir(pasta_video)
    while ha_frames:
        cv2.imwrite(pasta_video + "/frame%d.jpg" % count, frame)
        ha_frames, frame = video.read()
        count += 1
    print("Processo de separação concluído.")


print ("Iniciando processo de rastreamento")

objeto = cv2.imread(objeto_filename, 1)
h, w, _ = objeto.shape

pasta_saida = "saida_" + video_filename
if not os.path.isdir(pasta_saida):
    os.mkdir(pasta_saida)

for frame in os.listdir(pasta_video):
    img = cv2.imread(pasta_video + "/" + frame, 1)
    res = cv2.matchTemplate(img, objeto, cv2.TM_CCORR)
    min_val, max_val, min_loc, max_loc = cv2.minMaxLoc(res)
    top_left = max_loc
    bottom_right = (top_left[0] + w, top_left[1] + h)
    cv2.rectangle(img, top_left, bottom_right, 255, 2)
    cv2.imwrite(pasta_saida + "/" + frame.replace('frame', ''), img)

print("Frames de rastreamento gerados, iniciando conversão para vídeo...")

img_array = []
arquivos_final = os.listdir(pasta_saida)
arquivos_final.sort(key=lambda x: int(x.replace('.jpg', '')))

for frame in arquivos_final:
    img = cv2.imread(pasta_saida + "/" + frame, 1)
    height, width, layers = img.shape
    size = (width,height)
    img_array.append(img)

fps_video = cv2.VideoCapture(video_filename)
fps = fps_video.get(cv2.CAP_PROP_FPS)

out = cv2.VideoWriter('rastreio_'+video_filename.split('.')[0]+'.avi',cv2.VideoWriter_fourcc(*'DIVX'), fps, size)

for i in range(len(img_array)):
    out.write(img_array[i])
out.release()

print("Vídeo com resultado final salvo em: %s" % ('rastreio_'+video_filename.split('.')[0]+'.avi'))
