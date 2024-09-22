<?php
// Verilen seviyeye göre veriyi çekme fonksiyonu
function getLevelData($level) {
    $file = 'EXPdat.txt'; // TXT dosyanızın yolu
    $handle = fopen($file, 'r'); // Dosyayı okuma modunda açıyoruz
    
    $levelInfo = []; // Seviye bilgisini tutacak dizi

    // Satırları tek tek okuma
    while (($line = fgets($handle)) !== false) {
        // Satırı boşluklara göre ayırıyoruz (birden fazla boşluk veya tab olabilir)
        $data = preg_split('/\s+/', trim($line));

        // $data[0] = Level, $data[1] = XP, $data[2] = TotalXP
        if ($data[0] == $level) {
            $levelInfo = [
                'level' => $data[0],
                'xp' => $data[1],
                'totalXP' => $data[2]
            ];
            break; // İlgili seviye bulununca döngüden çık
        }
    }

    fclose($handle); // Dosyayı kapat
    
    return $levelInfo; // Seviye bilgisini döndür
}

// Form gönderildiyse
if (isset($_GET['level'])) {
    $level = intval($_GET['level']); // Kullanıcıdan gelen seviyeyi al
    $levelData = getLevelData($level); // Seviye verisini bul

    // Veriyi ekrana yazdır
    if ($levelData) {
        echo 'Seviye: ' . $levelData['level'] . '<br>';
        echo 'XP: ' . $levelData['xp'] . '<br>';
        echo 'Toplam XP: ' . $levelData['totalXP'];
    } else {
        echo 'Veri bulunamadı.';
    }
}
?>
