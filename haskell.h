data Mes = Enero | Febrero | Marzo | Abril | Mayo | Junio | Julio | Agosto | Septiembre | Octubre | Noviembre | Diciembre

vacaciones :: Mes -> Bool
vacaciones Enero = False
vacaciones Febrero = False
vacaiones Julio = False
vacaiones Diciembre = False
vacaiones otherwise = True

