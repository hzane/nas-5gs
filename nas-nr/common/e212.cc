#include "config.hh"
#include "field_meta.hh"
#include "format.hh"

extern const value_string e212_codes[];
extern const value_string mnc_codes[];

/* *   8   7   6   5   4   3   2   1
 * +---+---+---+---+---+---+---+---+
 * |  MCC digit 2  |  MCC digit 1  |  octet x
 * +---------------+---------------+
 * |  MNC digit 3  |  MCC digit 3  |  octet x+1
 * +---------------+---------------+
 * |  MNC digit 2  |  MNC digit 1  |  octet x+2
 * +---------------+---------------+
 *
 */
string mcc_string(const uint8_t* d, int length) {
    if (!d || length < 3) return string();
    auto       octet = static_cast< uint32_t >(d[0]);
    const auto mcc1  = octet & 0x0fu;
    const auto mcc2  = octet >> 4u;

    octet           = d[1];
    const auto mcc3 = octet & 0x0fu;

    const auto mcc = 100 * mcc1 + 10 * mcc2 + mcc3;

    if (mcc == 460) {
        return "China (460)";
    }
    return vstring(e212_codes, mcc);
}

string mcc_mnc_string(const uint8_t* d, int length) {
    if (!d || length < 3) return string();
    auto octet = d[1];

    /* MNC, Mobile network code (octet 3 bits 5 to 8, octet 4)  */
    const auto mnc3 = octet >> 4u;

    octet           = d[2];
    const auto mnc1 = octet & 0x0fu;
    const auto mnc2 = octet >> 4u;

    auto       mnc  = 100 * mnc1 + 10 * mnc2 + mnc3;

    if (mnc3 > 9) mnc = mnc1 * 10 + mnc2; // 2 digits

    return vstring(mnc_codes, mnc);
}

// https://en.wikipedia.org/wiki/Mobile_Network_Codes_in_ITU_region_4xx_(Asia)#China_-_CN
// only support chinese mnc
extern const value_string mnc_codes[] = {
    {0, "China Mobile GSM"},
    {1, "China Unicom"},
    {2, "China Mobile GSM"},
    {3, "China Telecom"},
    {4, "China Space Mobile Satellite Telecommunications Co. Ltd (China Spacecom)"},
    {5, "China Telecom"},
    {6, "China Unicom"},
    {7, "China Mobile GSM"},
    {8, "China Mobile"},
    {9, "China Unicorm"},
    {11, "China Unicom"},
    {20, "China Tietong"},
    {1666665, "Unset"},
    {0, nullptr},
};

/*
 * Annex to ITU Operational Bulletin
 * No. 1019 - 1.I.2013
 *
 * COMPLEMENT TO ITU-T RECOMMENDATION E.212 (05/2008)
 *
 * Find the bulletins here:
 * http://www.itu.int/en/publications/ITU-T/Pages/publications.aspx?parent=T-SP&view=T-SP1
 */
extern const value_string e212_codes[] = {
    {202, "Greece"},
    {203, "Unassigned"},
    {204, "Netherlands (Kingdom of the)"},
    {205, "Unassigned"},
    {206, "Belgium"},
    {207, "Unassigned"},
    {208, "France"},
    {212, "Monaco (Principality of)"},
    {213, "Andorra (Principality of)"},
    {214, "Spain"},
    {215, "Unassigned"},
    {216, "Hungary (Republic of)"},
    {217, "Unassigned"},
    {218, "Bosnia and Herzegovina"},
    {219, "Croatia (Republic of)"},
    {220, "Serbia (Republic of)"},
    {222, "Italy"},
    {225, "Vatican City State"},
    {226, "Romania"},
    {228, "Switzerland (Confederation of)"},
    {230, "Czech Republic"},
    {231, "Slovak Republic"},
    {232, "Austria"},
    {234, "United Kingdom of Great Britain and Northern Ireland"},
    {235, "United Kingdom of Great Britain and Northern Ireland"},
    {238, "Denmark"},
    {240, "Sweden"},
    {242, "Norway"},
    {244, "Finland"},
    {246, "Lithuania (Republic of)"},
    {247, "Latvia (Republic of)"},
    {248, "Estonia (Republic of)"},
    {250, "Russian Federation"},
    {255, "Ukraine"},
    {256, "Unassigned"},
    {257, "Belarus (Republic of)"},
    {259, "Moldova (Republic of)"},
    {260, "Poland (Republic of)"},
    {262, "Germany (Federal Republic of)"},            
    {266, "Gibraltar"},
    {268, "Portugal"},
    {270, "Luxembourg"},
    {272, "Ireland"},
    {274, "Iceland"},
    {276, "Albania (Republic of)"},
    {278, "Malta"},
    {280, "Cyprus (Republic of)"},
    {282, "Georgia"},
    {283, "Armenia (Republic of)"},
    {284, "Bulgaria (Republic of)"},
    {286, "Turkey"},
    {288, "Faroe Islands"},
    {290, "Greenland (Denmark)"},
    {292, "San Marino (Republic of)"},
    {293, "Slovenia (Republic of)"},
    {294, "The Former Yugoslav Republic of Macedonia"},
    {295, "Liechtenstein (Principality of)"},
    {297, "Montenegro (Republic of)"},
    {302, "Canada"},
    {308,
     "Saint Pierre and Miquelon (Collectivite territoriale de la Republique francaise)"},
    {310, "United States of America"},
    {311, "United States of America"},
    {312, "United States of America"},
    {313, "United States of America"},
    {314, "United States of America"},
    {315, "United States of America"},
    {316, "United States of America"},
    {330, "Puerto Rico"},
    {332, "United States Virgin Islands"},
    {334, "Mexico"},
    {338, "Jamaica"},
    {340, "Martinique/Guadeloupe (French Departments of)"},
    {342, "Barbados"},
    {344, "Antigua and Barbuda"},
    {346, "Cayman Islands"},
    {348, "British Virgin Islands"},
    {350, "Bermuda"},
    {352, "Grenada"},
    {354, "Montserrat"},
    {356, "Saint Kitts and Nevis"},
    {358, "Saint Lucia"},
    {360, "Saint Vincent and the Grenadines"},
    {362, "Netherlands Antilles"},
    {363, "Aruba"},
    {364, "Bahamas (Commonwealth of the)"},
    {365, "Anguilla"},
    {366, "Dominica (Commonwealth of)"},
    {367, "Unassigned"},
    {368, "Cuba"},
    {369, "Unassigned"},
    {370, "Dominican Republic"},
    {371, "Unassigned"},
    {372, "Haiti (Republic of)"},
    {373, "Unassigned"},
    {374, "Trinidad and Tobago"},
    {375, "Unassigned"},
    {376, "Turks and Caicos Islands"},
    {400, "Azerbaijani Republic"},
    {401, "Kazakhstan (Republic of)"},
    {402, "Bhutan (Kingdom of)"},
    {404, "India (Republic of)"},
    {405, "India (Republic of)"},
    {406, "India (Republic of)"},
    {410, "Pakistan (Islamic Republic of)"},
    {412, "Afghanistan"},
    {413, "Sri Lanka (Democratic Socialist Republic of)"},
    {414, "Myanmar (Union of)"},
    {415, "Lebanon"},
    {416, "Jordan (Hashemite Kingdom of)"},
    {417, "Syrian Arab Republic"},
    {418, "Iraq (Republic of)"},
    {419, "Kuwait (State of)"},
    {420, "Saudi Arabia (Kingdom of)"},
    {421, "Yemen (Republic of)"},
    {422, "Oman (Sultanate of)"},
    {424, "United Arab Emirates"},
    {425, "Israel (State of)"},
    {426, "Bahrain (Kingdom of)"},
    {427, "Qatar (State of)"},
    {428, "Mongolia"},
    {429, "Nepal"},
    {430, "United Arab Emirates (Abu Dhabi)"},
    {431, "United Arab Emirates (Dubai)"},
    {432, "Iran (Islamic Republic of)"},
    {434, "Uzbekistan (Republic of)"},
    {436, "Tajikistan (Republic of)"},
    {437, "Kyrgyz Republic"},
    {438, "Turkmenistan"},
    {440, "Japan"},
    {441, "Japan"},
    {450, "Korea (Republic of)"},
    {452, "Viet Nam (Socialist Republic of)"},
    {454, "Hongkong, China"},
    {455, "Macao, China"},
    {456, "Cambodia (Kingdom of)"},
    {457, "Lao People's Democratic Republic"},
    {460, "China (People's Republic of)"},
    {461, "China (People's Republic of)"},
    {466, "Taiwan, China"},
    {467, "Democratic People's Republic of Korea"},
    {470, "Bangladesh (People's Republic of)"},
    {472, "Maldives (Republic of)"},
    {502, "Malaysia"},
    {505, "Australia"},
    {510, "Indonesia (Republic of)"},
    {514, "Democratic Republic of Timor-Leste"},
    {515, "Philippines (Republic of the)"},
    {520, "Thailand"},
    {525, "Singapore (Republic of)"},
    {528, "Brunei Darussalam"},
    {530, "New Zealand"},
    {534, "Previously assigned to Northern Mariana Islands (Commonwealth of the)"},
    {535, "Previously assigned to Guam"},
    {536, "Nauru (Republic of)"},
    {537, "Papua New Guinea"},
    {538, "Unassigned"},
    {539, "Tonga (Kingdom of)"},
    {540, "Solomon Islands"},
    {541, "Vanuatu (Republic of)"},
    {542, "Fiji (Republic of)"},
    {543, "Wallis and Futuna (Territoire francais d'outre-mer)"},
    {544, "American Samoa"},
    {545, "Kiribati (Republic of)"},
    {546, "New Caledonia (Territoire francais d'outre-mer)"},
    {547, "French Polynesia (Territoire francais d'outre-mer)"},
    {548, "Cook Islands"},
    {549, "Samoa (Independent State of)"},
    {550, "Micronesia (Federated States of)"},
    {551, "Marshall Islands (Republic of the)"},
    {552, "Palau (Republic of)"},
    {553, "Tuvalu"},
    {555, "Niue"},
    {602, "Egypt (Arab Republic of)"},
    {603, "Algeria (People's Democratic Republic of)"},
    {604, "Morocco (Kingdom of)"},
    {605, "Tunisia"},
    {606, "Libya (Socialist People's Libyan Arab Jamahiriya)"},
    {607, "Gambia (Republic of the)"},
    {608, "Senegal (Republic of)"},
    {609, "Mauritania (Islamic Republic of)"},
    {610, "Mali (Republic of)"},
    {611, "Guinea (Republic of)"},
    {612, "Cote d'Ivoire (Republic of)"},
    {613, "Burkina Faso"},
    {614, "Niger (Republic of the)"},
    {615, "Togolese Republic"},
    {616, "Benin (Republic of)"},
    {617, "Mauritius (Republic of)"},
    {618, "Liberia (Republic of)"},
    {619, "Sierra Leone"},
    {620, "Ghana"},
    {621, "Nigeria (Federal Republic of)"},
    {622, "Chad (Republic of)"},
    {623, "Central African Republic"},
    {624, "Cameroon (Republic of)"},
    {625, "Cape Verde (Republic of)"},
    {626, "Sao Tome and Principe (Democratic Republic of)"},
    {627, "Equatorial Guinea (Republic of)"},
    {628, "Gabonese Republic"},
    {629, "Congo (Republic of the)"},
    {630, "Democratic Republic of the Congo"},
    {631, "Angola (Republic of)"},
    {632, "Guinea-Bissau (Republic of)"},
    {633, "Seychelles (Republic of)"},
    {634, "Sudan (Republic of the)"},
    {635, "Rwanda (Republic of)"},
    {636, "Ethiopia (Federal Democratic Republic of)"},
    {637, "Somali Democratic Republic"},
    {638, "Djibouti (Republic of)"},
    {639, "Kenya (Republic of)"},
    {640, "Tanzania (United Republic of)"},
    {641, "Uganda (Republic of)"},
    {642, "Burundi (Republic of)"},
    {643, "Mozambique (Republic of)"},
    {644, "Unassigned"},
    {645, "Zambia (Republic of)"},
    {646, "Madagascar (Republic of)"},
    {647, "French Departments and Territories in the Indian Ocean"},
    {648, "Zimbabwe (Republic of)"},
    {649, "Namibia (Republic of)"},
    {650, "Malawi"},
    {651, "Lesotho (Kingdom of)"},
    {652, "Botswana (Republic of)"},
    {653, "Swaziland (Kingdom of)"},
    {654, "Comoros (Union of the)"},
    {655, "South Africa (Republic of)"},
    {657, "Eritrea"},
    {659, "South Sudan"},
    {702, "Belize"},
    {704, "Guatemala (Republic of)"},
    {706, "El Salvador (Republic of)"},
    {708, "Honduras (Republic of)"},
    {710, "Nicaragua"},
    {712, "Costa Rica"},
    {714, "Panama (Republic of)"},
    {715, "Unassigned"},
    {716, "Peru"},
    {722, "Argentina"},
    {724, "Brazil (Federative Republic of)"},
    {730, "Chile"},
    {732, "Colombia (Republic of)"},
    {734, "Venezuela (Bolivarian Republic of)"},
    {736, "Bolivia (Republic of)"},
    {738, "Guyana"},
    {740, "Ecuador"},
    {742, "French Guiana (French Department of)"},
    {744, "Paraguay (Republic of)"},
    {746, "Suriname (Republic of)"},
    {748, "Uruguay (Eastern Republic of)"},
    {750, "Falkland Islands (Malvinas)"},    
    {901, "International Mobile, shared code"},
    {1665, "Unset"},
    {0, nullptr},
};

