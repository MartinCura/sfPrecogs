# Leo archivos csv iniciales
train = read.csv("train.csv")
test  = read.csv("test.csv")

# En train2 parseo la fecha y hora
train2 <- train
train2$Dates <- as.character(train2$Dates)
train2$Year <-   sapply(train2$Dates, FUN=function(x) { strsplit(x, split = '[- :]')[[1]][1] })
train2$Month <-  sapply(train2$Dates, FUN=function(x) { strsplit(x, split = '[- :]')[[1]][2] })
train2$Day <-    sapply(train2$Dates, FUN=function(x) { strsplit(x, split = '[- :]')[[1]][3] })
train2$Hour <-   sapply(train2$Dates, FUN=function(x) { strsplit(x, split = '[- :]')[[1]][4] })
train2$Minute <- sapply(train2$Dates, FUN=function(x) { strsplit(x, split = '[- :]')[[1]][5] })

# Símil test2
test2 <- test
test2$Dates <- as.character(test2$Dates)
test2$Year <-   sapply(test2$Dates, FUN=function(x) { strsplit(x, split = '[- :]')[[1]][1] })
test2$Month <-  sapply(test2$Dates, FUN=function(x) { strsplit(x, split = '[- :]')[[1]][2] })
test2$Day <-    sapply(test2$Dates, FUN=function(x) { strsplit(x, split = '[- :]')[[1]][3] })
test2$Hour <-   sapply(test2$Dates, FUN=function(x) { strsplit(x, split = '[- :]')[[1]][4] })
test2$Minute <- sapply(test2$Dates, FUN=function(x) { strsplit(x, split = '[- :]')[[1]][5] })

# Guardo en *Nuevo las columnas que quiero quedarme
testNuevo  <- data.frame(Id = test2$Id, PdDistrict = test2$PdDistrict, Address = test2$Address, X = test2$X, Y = test2$Y, Year = test2$Year, Month = test2$Month, Day = test2$Day, DayOfWeek = test2$DayOfWeek, Hour = test2$Hour, Minute = test2$Minute)
trainNuevo <- data.frame(Category = train2$Category, PdDistrict = train2$PdDistrict, Address = train2$Address, X = train2$X, Y = train2$Y, Year = train2$Year, Month = train2$Month, DayOfWeek = train2$DayOfWeek, Day = train2$Day, Hour = train2$Hour, Minute = train2$Minute)
#write.csv(trainNuevo, file = "train911.csv", row.names = FALSE)
#write.csv(testNuevo, file = "test911.csv", row.names = FALSE)     # Fin 911

train2$X[train2$X == -120.5] <- NA
train2$Y[train2$Y ==   90]   <- NA
train4 <- train2[complete.cases(train2),]
# Creo X, Y reducidos
train4$X <- sapply(train3$X, FUN=function(x) { round(x*1000) }) # Elige tamaño del cuadrante (cortando después del 3er decimal)
train4$Y <- sapply(train3$Y, FUN=function(x) { round(x*1000) })
train4$X <- sapply(train4$X, FUN=function(x) { x+122514 }) # Normaliza corrimiento
train4$Y <- sapply(train4$Y, FUN=function(x) { x-37708 })

# Ignoro outfliers de coordenadas
trainNuevo$X[trainNuevo$X == -120.5] <- NA
trainNuevo$Y[trainNuevo$Y ==   90]   <- NA
trainNuevo <- trainNuevo[complete.cases(trainNuevo),]
trainNuevo$Xr <- train4$X
trainNuevo$Yr <- train4$Y

# Calculo cuadrante ("hash")
trainNuevo$Cuad <- mapply(FUN=function(x,y) { x+y*151 }, trainNuevo$Xr, trainNuevo$Yr)
trainNuevo$Cuad2<- mapply(FUN=function(x,y) { x*131+y }, trainNuevo$Xr, trainNuevo$Yr)

test1911 <- read.csv("test911.csv")
# Proceso similar para test, pero no puedo ignorar los outflierscom
test1911$Xr <- sapply(test1911$X, FUN=function(x) { round(x*1000) })
test1911$Yr <- sapply(test1911$Y, FUN=function(x) { round(x*1000) })
test1911$Xr <- sapply(test1911$Xr, FUN=function(x) { x+122514 })
test1911$Yr <- sapply(test1911$Yr, FUN=function(x) { x-37708 })
test1911$Cuad <- mapply(FUN=function(x,y) { x+y*151 }, test1911$Xr, test1911$Yr)
test1911$Cuad2<- mapply(FUN=function(x,y) { x*131+y }, test1911$Xr, test1911$Yr)

# Modificación 2311: Borro Id de test
testSinId <- test1911[,2:15]

# 0712 Agregué Cuad2

# Escribo archivos csv intervenidos
write.csv(trainNuevo, file = "trainM.csv", row.names = FALSE)
write.csv(testSinId, file = "testM.csv", row.names = FALSE)
