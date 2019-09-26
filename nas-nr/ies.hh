#pragma once
#include <cstdint>
#include <vector>
#include "common/nas.hh"

using octet_t = std::vector< uint8_t >;
using bit4_t  = uint8_t;
using bit1_t  = uint8_t;
using bit3_t  = uint8_t;
using bit2_t  = uint8_t;


/*
9.11.2.1A	DNN
8	7	6	5	4	3	2	1
DNN IEI	octet 1
Length of DNN contents	octet 2
DNN value	octet 3  octet n
*/
using dnn_t = octet_t;

/*
9.11.2.2	EAP message
8	7	6	5	4	3	2	1
EAP message IEI	octet 1
Length of EAP message contents	octet 2  octet 3
EAP message	octet 4  octet n
*/
using eap_t = octet_t;

/*
9.11.2.6	Intra N1 mode NAS transparent container
8	7	6	5	4	3	2	1
Intra N1 mode NAS transparent container IEI	octet 1
Length of Intra N1 mode NAS transparent container contents	octet 2
Message authentication code	octet 3  octet 6
Type of ciphering algorithm	Type of integrity protection algorithm	octet 7
0	0 Spare	0	KACF	TSC	Key set identifier in 5G	octet 8
Sequence number	octet 9
*/
struct intra_n1_mode_container_t {
    bit4_t  integrity_algo;
    bit4_t  ciphering_algo;
    bit3_t  nksi;
    bit1_t  tsc;
    bit1_t  kacf;
    uint8_t seq_no;
};

/*
9.11.2.7	N1 mode to S1 mode NAS transparent container
8	7	6	5	4	3	2	1
N1 mode to S1 mode NAS transparent container IEI	octet 1
Sequence number	octet 2
*/
struct n1_mode_to_s1_mode_container_t {
    uint8_t seq_no;
};

/*
9.11.2.8	S-NSSAI
8	7	6	5	4	3	2	1
S-NSSAI IEI	octet 1
Length of S-NSSAI contents	octet 2
SST	octet 3
SD	octet 4*  octet 6*
Mapped HPLMN SST	octet 7*
Mapped HPLMN SD	octet 8*  octet 10*
*/
struct s_nssai_t {
    uint8_t          sst;
    opt_t< octet_3 > sd;
    opt_t< uint8_t > mapped_hplmn_sst;
    opt_t< octet_3 > mapped_hplmn_sd;
};

/*
8	7	6	5	4	3	2	1
S1 mode to N1 mode NAS transparent container IEI	octet 1
Length of S1 mode to N1 mode NAS transparent container contents	octet 2
Message authentication code	octet 3  octet 6
Type of ciphering algorithm	Type of integrity protection algorithm	octet 7	0 Spare
NCC	TSC	Key set identifier in 5G	octet 8
0 Spare	octet 9  octet 10
0 Spare
*/
struct s1_mode_to_n1_mode_container_t {
    octet_4 auth_code;
    bit4_t  integrity_algo;
    bit4_t  ciphering_algo;
    bit3_t  nksi;
    bit1_t  tsc;
    bit4_t  ncc;
};

/*
9.11.3.1	5GMM capability
8	7	6	5	4	3	2	1
5GMM capability IEI	octet 1
Length of 5GMM capability contents	octet 2	SGC
5G-HC-CP CIoT	N3 data	5G-CP CIoT	RestrictEC	LPP	HO attach	S1 mode	octet 3
0 Spare	5G-UP CIoT	5GSRVCC	octet 4*
0	octet 5*-15*
Spare	0
*/
struct nmm_capability_t {
    bit1_t nhccp_ciot;
    bit1_t n3data;
    bit1_t ncp_ciot;
    bit1_t restrict_ec;
    bit1_t lpp;
    bit1_t ho_attach;
    bit1_t s1_mode;
    bit1_t nsrvcc;
    bit1_t nup_ciot;
};

/*
9.11.3.2	5GMM cause
8	7	6	5	4	3	2	1
5GMM cause IEI	octet 1
Cause value	octet 2
*/
using nmm_cause_t = uint8_t;

/*
9.11.3.2A	5GS DRX parameters
8	7	6	5	4	3	2	1
5GS DRX parameters IEI	octet 1
Length of 5GS DRX parameters contents	octet 2
0	DRX value
spare	DRX value	octet 3
*/
using drx_parameters = bit4_t;

/*
8	7	6	5	4	3	2
5GS identity type IEI	0 spare	Type of identity
*/
using nid_type_t = bit3_t;

struct mcc_mnc_t {
    uint16_t mcc;
    uint16_t mnc;
};

/*
9.11.3.4	5GS mobile identity
8	7	6	5	4	3	2	1
5GS mobile identity IEI	octet 1
Length of 5GS mobile identity contents	octet2  octet 3
1	0 spare	Type of identity	octet 4
MCC digit 2	MCC digit 1	octet 5
MNC digit 3	MCC digit 3	octet 6
MNC digit 2	MNC digit 1	octet 7
AMF Region ID	octet 8
AMF Set ID	octet 9
AMF Set ID (continued)	AMF Pointer	octet 10
5G-TMSI	octet 11
5G-TMSI (continued)	octet 12
5G-TMSI (continued)	octet 13
5G-TMSI (continued)	octet 14
*/
struct nguti_mid_t {
    bit3_t    type;
    mcc_mnc_t mccmnc;
    bita_t    afm_region_id;
    bit6_t    amf_pointer;
    octet_4   tmsi;
};

/*
Figure 9.11.3.4.1: 5GS mobile identity information element for type of identity "5G-GUTI"
8	7	6	5	4	3	2	1
5GS mobile identity IEI	octet 1
Length of 5GS mobile identity contents	octet 2  octet 3
Identity digit 1	odd/ even indic	Type of identity	octet 4
Identity digit p+1	Identity digit p	octet 5*

Figure 9.11.3.4.2: 5GS mobile identity information element for type of identity or "IMEI"
or "IMEISV" 8	7	6	5	4	3	2	1 5GS mobile identity IEI	octet 1 Length of 5GS
mobile identity contents	octet 2  octet 3 0 spare	SUPI format	0 spare	Type of
identity	octet 4 MCC digit 2	MCC digit 1	octet 5 MNC digit 3	MCC digit 3	octet 6 MNC
digit 2	MNC digit 1	octet 7 Routing indicator digit 2	Routing indicator digit 1 octet 8
Routing indicator digit 4	Routing indicator digit 3	octet 9
0 Spare	Protection scheme Id	octet 10
Home network public key identifier	octet 11
Scheme output	octet 12 - x

Figure 9.11.3.4.3: 5GS mobile identity information element for type of identity "SUCI" and
SUPI format "IMSI" 8	7	6	5	4	3	2	1 MSIN digit 2	MSIN digit 1	octet 12 …
MSIN digit n+1	MSIN digit n	octet x

Figure 9.11.3.4.3a: Scheme output for type of identity "SUCI", SUPI format "IMSI" and
Protection scheme Id "Null scheme" 8	7	6	5	4	3	2	1 5GS mobile identity IEI
octet 1 Length of 5GS mobile identity contents	octet 2  octet 3 0 Spare	SUPI format	0
Spare	Type of identity	octet 4 SUCI NAI	octet 5 - y

Figure 9.11.3.4.4: 5GS mobile identity information element for type of identity "SUCI" and
SUPI format "Network specific identifier" 8	7	6	5	4	3	2	1 5GS mobile identity
IEI	octet 1 Length of 5GS mobile identity contents	octet 2  octet 3 1	0 spare	Type of
identity	octet 4 AMF Set ID	octet 5 AMF Set ID (continued)	AMF Pointer	octet 6
5G-TMSI	octet 7
5G-TMSI (continued)	octet 8
5G-TMSI (continued)	octet 9
5G-TMSI (continued)	octet 10

Figure 9.11.3.4.5: 5GS mobile identity information element for type of identity
"5G-S-TMSI" 8	7	6	5	4	3	2	1 5GS mobile identity IEI	octet 1 Length of 5GS
mobile identity contents	octet 2  octet 3 0	Type of identity	octet 4 spare	Type
of identity	octet 4

Figure 9.11.3.4.6: 5GS mobile identity information element for type of identity "No
identity" 8	7	6	5	4	3	2	1 5GS mobile identity IEI	octet 1 Length of 5GS
mobile identity contents	octet 2  octet 3 0 spare	Type of identity	octet 4 MAC
address	octet 5  octet 10
*/

/*
9.11.3.5	5GS network feature support
8	7	6	5	4	3	2
5GS network feature support IEI
Length of 5GS network feature support contents
MPSI	IWK N26	EMF	EMC	IMS- VoPS-N3GPP	IMS- VoPS-3GPP
0 Spare	5G-UP CIoT	5G-HC-CP CIoT	N3 data	5G-CP CIoT	RestrictEC	MCSI	EMCN3

Spare
*/
struct nnetwork_feature_support_t {
    bit1_t ims_vops_3gpp;
    bit1_t ims_vops_n3gpp;
    bit2_t emc;
    bit2_t emf;
    bit1_t iwk_n26;
    bit1_t mpsi;
    bit1_t emcn3;
    bit1_t mcsi;
    bit1_t restrict_ec;
    bit1_t ncp_ciot;
    bit1_t n3data;
    bit1_t nhc_cp_ciot;
    bit1_t nup_ciot;
};

/*
8	7	6	5	4	3	2	1
5GS registration result IEI	octet 1
Length of 5GS registration result contents	octet 2
0 Spare	SMS allowed	5GS registration result value
*/
struct nregistration_result_t {
    bit3_t result;
    bit1_t sms_allowed;
};

/*
8	7	6	5	4	3	2	1
5GS registration type IEI	FOR	5GS registration type value	octet 1
*/
using nregistration_type_t = bit3_t;

/*
8	7	6	5	4	3	2	1
5GS tracking area identity IEI	octet 1
MCC digit 2	MCC digit 1	octet 2
MNC digit 3	MCC digit 3	octet 3
MNC digit 2	MNC digit 1	octet 4
TAC	octet 5
TAC (continued)	octet 6
TAC (continued)	octet 7
*/

struct ntracking_area_id_t {
    mcc_mnc_t mcc_mnc;
    octet_3   tac;
};

struct ntai_list_00_t {
    bit4_t                 number; // +1
    bit2_t                 type; // 00
    mcc_mnc_t              mccmnc;
    std::vector< octet_3 > tac;
};
struct ntai_list_01_t {
    bit4_t                 number; // +1
    bit2_t                 type; // 01
    mcc_mnc_t              mccmnc;
    octet_3                tac;
};
struct ntai_list_10_t {
    bit4_t                             number; // +1
    bit2_t                             type;   // 01
    std::vector< ntracking_area_id_t > ids;
};
/*
8	7	6	5	4	3	2	1
5GS tracking area identity list IEI	octet 1
Length of 5GS tracking area identity list contents	octet 2
Partial tracking area identity list 1	octet 3  octet i
Partial tracking area identity list 2	octet i+1*  octet l*
…	octet l+1*  octet m*
Partial tracking area identity list p	octet m+1*  octet n*
*/
struct ntracking_area_id_list_t {
    bit2_t                            type;
    std::shared_ptr< ntai_list_00_t > l_00;
    std::shared_ptr< ntai_list_01_t > l_01;
    std::shared_ptr< ntai_list_10_t > l_10;
};

/*
8	7	6	5	4	3	2	1
0 Spare	Type of list	Number of elements	octet 1
MCC digit 2	MCC digit 1	octet 2
MNC digit 3	MCC digit 3	octet 3
MNC digit 2	MNC digit 1	octet 4
TAC 1	octet 5
TAC 1 (continued)	octet 6
TAC 1 (continued)	octet 7
…
…
TAC k	octet 3k+2*
TAC k (continued)	octet 3k+3*
TAC k (continued)	octet 3k+4*


8	7	6	5	4	3	2	1
0 Spare	Type of list	Number of elements	octet 1
MCC digit 2	MCC digit 1	octet 2
MNC digit 3	MCC digit 3	octet 3
MNC digit 2	MNC digit 1	octet 4
TAC 1	octet 5
TAC 1 (continued)	octet 6
TAC 1 (continued)	octet 7


8	7	6	5	4	3	2	1
0 Spare	Type of list	Number of elements	octet 1
MCC digit 2	MCC digit 1	octet 2
MNC digit 3	MCC digit 3	octet 3
MNC digit 2	MNC digit 1	octet 4
TAC 1	octet 5
TAC 1 (continued)	octet 6
TAC 1 (continued)	octet 7
MCC digit 2	MCC digit 1	octet 8*
MNC digit 3	MCC digit 3	octet 9*
MNC digit 2	MNC digit 1	octet 10*
TAC 2	octet 11*
TAC 2 (continued)	octet 12*
TAC 2 (continued)	octet 13*
…
…
MCC digit 2	MCC digit 1	octet 6k-4*
MNC digit 3	MCC digit 3	octet 6k-3*
MNC digit 2	MNC digit 1	octet 6k-2*
TAC k	octet 6k-1*
TAC k (continued)	octet 6k*
TAC k (continued)	octet 6k+1*
*/


/*
9.11.3.9A	5GS update type
8	7	6	5	4	3	2	1
5GS update type IEI	octet 1
Length of 5GS update type	octet 2
0 Spare	PNB-CIoT	NG-RAN-RCU	SMS requested
*/
struct nupdate_type_t {
    bit1_t sms_requested;
    bit1_t nran_rcu;
    bit2_t pnb_ciot;
};

/*
9.11.3.10	ABBA
8	7	6	5	4	3	2	1
ABBA IEI	octet 1
Length of ABBA contents	octet 2
ABBA contents	octet 3  octet n
*/
using abba_t = octet_t;

/*
9.11.3.11	Access type
8	7	6	5	4	3	2	1
Access type IEI	0 spare	Access type	octet 1
*/
using access_type_t = bit2_t;

/*
9.11.3.12	Additional 5G security information
8	7	6	5	4	3	2	1
Additional 5G security parameters IEI	octet 1
Length of Additional 5G security parameters contents	octet 2
0 Spare	RINMR	HDP
*/
struct additional_5g_security_inforation_t {
    bit1_t hdp;
    bit1_t rinmr;
};

/*
9.11.3.13	Allowed PDU session status
8	7	6	5	4	3	2	1
Allowed PDU session status IEI	octet 1
Length of Allowed PDU session status contents	octet 2
PSI (7)	PSI (6)	PSI (5)	PSI (4)	PSI (3)	PSI (2)	PSI (1)	PSI (0)	octet 3
PSI (15)	PSI (14)	PSI (13)	PSI (12)	PSI (11)	PSI (10)	PSI (9)	PSI (8)
octet 4
0
Spare	octet 5* -34*
*/
using allowed_pdu_session_status_t = octet_2;

/*
9.11.3.18	Configuration update indication
8	7	6	5	4	3	2	1
Configuration update indication IEI	0 Spare	RED	ACK	octet 1
*/
struct configuration_update_indication_t {
    bit1_t ack;
    bit1_t red;
};

/*
9.11.3.20	De-registration type
8	7	6	5	4	3	2	1
De-registration type IEI	Switch off	Re-registration required	Access type	octet 1
*/
struct deregistration_type_t {
    bit2_t access_type;
    bit1_t reregistration_required;
    bit1_t switch_off;
};

/*
9.11.3.24	EPS NAS message container
8	7	6	5	4	3	2	1
EPS NAS message container IEI	octet 1
Length of EPS NAS message container contents	octet 2  octet 3
EPS NAS message container	octet 4  octet n
*/
using eps_nas_message_t = octet_t;

/*
9.11.3.29	LADN indication
8	7	6	5	4	3	2	1
LADN indication IEI	octet 1
Length of LADN indication contents	octet 2 octet 3
LADN DNN value 1	octet 4*  octet a*
LADN DNN value 2	octet a+1*  octet b*
…	octet b+1*  octet g*
LADN DNN value n	octet g+1*  octet h*
*/
struct ladn_indication_t {
    std::vector< dnn_t > dnn;
};

/*
9.11.3.30	LADN information
8	7	6	5	4	3	2	1
LADN information IEI	octet 1
Length of LADN information contents	octet 2 octet 3
LADN 1	octet 4  octet a
LADN 2	octet a+1*  octet b*
…	octet b+1*  octet g*
LADN n	octet g+1*  octet h*
*/

struct ladn_information_t {
    struct ladn_t {
        dnn_t                    dnn;
        ntracking_area_id_list_t ntai;
    };
    std::vector< ladn_t > ladn;
};
/*
Figure 9.11.3.30.1: LADN information information element
8	7	6	5	4	3	2	1
Length of DNN value	octet 4
DNN value	octet 5  octet m
5GS tracking area identity list	octet m+1  octet a
*/

/*
9.11.3.31	MICO indication
8	7	6	5	4	3	2	1
MICO indication IEI	0 Spare	SPRTI	RAAI	octet 1
*/
struct mico_indication_t {
    bit1_t raai;
    bit1_t sprti;
};

/*
9.11.3.32	NAS key set identifier
8	7	6	5	4	3	2	1
NAS key set identifier IEI	TSC	NAS key set identifier	octet 1
*/
struct nas_key_set_identifier_t {
    bit3_t nksi;
    bit1_t tsc;
};

struct nas_message_t;
/*
9.11.3.33	NAS message container
8	7	6	5	4	3	2	1
NAS message container IEI	octet 1
Length of NAS message container contents	octet 2
octet 3
octet 4
NAS message container contents
octet n
*/
using nas_message_container_t = nas_message_t;

/*
9.11.3.34	NAS security algorithms
8	7	6	5	4	3	2	1
NAS security algorithms IEI	octet 1
Type of ciphering algorithm	Type of integrity protection algorithm	octet 2
*/
struct nas_security_algorithm_t {
    bit4_t integrity_algo;
    bit4_t ciphering_algo;
};

/*
9.11.3.36	Network slicing indication
8	7	6	5	4	3	2	1
Network slicing indication IEI	0 Spare	DCNI	NSSCI	octet 1
*/
struct network_slicing_indication_t {
    bit1_t nssci;
    bit1_t dcni;
};

/*
9.11.3.37	NSSAI
8	7	6	5	4	3	2	1
NSSAI IEI	octet 1
Length of NSSAI contents	octet 2
S-NSSAI value 1	octet 3  octet m
S-NSSAI value 2	octet m+1*  octet n*
…	octet n+1*  octet u*
S-NSSAI value n	octet u+1*  octet v*
*/
struct nssai_t {
    std::vector< s_nssai_t > s_nssai;
};

/*
9.11.3.37A	NSSAI inclusion mode
8	7	6	5	4	3	2	1
NSSAI inclusion mode IEI	0 spare	NSSAI inclusion mode	octet 1
*/
using nssai_includion_mode_t = bit2_t;

/*
9.11.3.38	Operator-defined access category definitions
8	7	6	5	4	3	2	1
Operator-defined access category definitions IEI	octet 1
Length of operator-defined access category definitions contents	octet 2 octet 3
Operator-defined access category definition 1	octet 4  octet a
Operator-defined access category definition 2	octet a+1*  octet b*
…	octet b+1*  octet g*
Operator-defined access category definition 1 n	octet g+1*  octet h*

Figure 9.11.3.38.1: Operator-defined access category definitions information element
8	7	6	5	4	3	2	1
Length of operator-defined access category definition contents	octet 4
Precedence value	octet 5
PSAC	0 Spare	Operator-defined access category number	octet 6
Length of criteria	octet 7
Criteria	octet 8  octet a-1
0 Spare	Standardized access category	octet a*
*/
struct operator_defined_access_category_definition_t {
    uint8_t         precedence;
    bit5_t          number;
    bit2_t          spare;
    bit1_t          psac;
    octet_t         criteria;
    opt_t< bit5_t > standardized_access_category;
};

/*
9.11.3.39	Payload container
8	7	6	5	4	3	2	1
Payload container IEI	octet 1
Length of payload container contents

octet 4
*/
using payload_container_t = octet_t;


struct payload_container_multiple_t {
    using optional_ie_t = octet_t;
    struct entry_t {
        bit4_t type;
        // bit4_t                       optional_ie_number;
        std::vector< optional_ie_t > optional_ies;
        octet_t                      content;
    };

    // uint8_t number;
    std::vector< entry_t > entries;
};

/*
Figure 9.11.3.39.1: Payload container information element
8	7	6	5	4	3	2	1
Number of entries	octet 4
Payload container entry 1	octet 5  octet x2
Payload container entry 2	octet x2+1  octet x3
……	…
Payload container entry i	octet xi +1  octet n

Figure 9.11.3.39.2: Payload container contents with Payload container type "Multiple
payloads" 8	7	6	5	4	3	2	1 Length of Payload container entry	octet xi +1 octet
xi +2 Number of optional IEs	Payload container type	octet xi +3 Optional IE 1	octet
xi +4  octet y2 Optional IE 2	octet y2+1  octet y3 … Optional IE j	octet yj+1  octet
z Payload container entry contents	octet z+1  octet n

Figure 9.11.3.39.3: Payload container entry
8	7	6	5	4	3	2	1
Type of optional IE	octet xi +4
Length of optional IE	octet xi +5
Value of optional IE	octet xi +6  octet y2
*/

/*
9.11.3.40	Payload container type
8	7	6	5	4	3	2	1
Payload container type IEI	Payload container type value
*/
using payload_container_type_t = bit4_t;

/*
9.11.3.41	PDU session identity 2
8	7	6	5	4	3	2	1
PDU session identity 2 IEI	octet 1
PDU session identity 2 value	octet 2
*/
using pdu_session_identity_2_t = uint8_t;

/*
9.11.3.42	PDU session reactivation result
8	7	6	5	4	3	2	1
PDU session reactivation result IEI	octet 1
Length of PDU session reactivation result	octet 2
PSI (7)	PSI  (6)	PSI  (5)	PSI  (4)	PSI  (3)	PSI  (2)	PSI  (1)	PSI (0)
octet 3 PSI  (15)	PSI  (14)	PSI  (13)	PSI  (12)	PSI  (11)	PSI  (10)	PSI (9)
PSI  (8)	octet 4 octet 5* -34*
*/
struct pdu_session_reactivation_result_t {
    uint8_t psi_a;
    uint8_t psi_b;
};

/*
9.11.3.43	PDU session reactivation result error cause
8	7	6	5	4	3	2	1
PDU session reactivation result error cause IEI	octet 1
Length of PDU session reactivation result error cause	octet 2
octet 3
PDU session ID	octet 4
cause value	octet 5
….
PDU session ID	octet 514*
cause value	octet 515*
*/
struct pdu_session_reactivation_result_error_cause_t {
    struct cause_t {
        uint8_t pdu_session_id;
        uint8_t cause;
    };
    std::vector< cause_t > cause;
};

/*
9.11.3.44	PDU session status
8	7	6	5	4	3	2	1
PDU session status IEI	octet 1
Length of PDU session status contents	octet 2
PSI (7)	PSI (6)	PSI (5)	PSI (4)	PSI (3)	PSI (2)	PSI (1)	PSI (0)	octet 3
PSI (15)	PSI (14)	PSI (13)	PSI (12)	PSI (11)	PSI (10)	PSI (9)	PSI (8)
octet 4 0	octet 5*- spare	34*
*/
struct pdu_session_status_t {
    uint8_t psi_a;
    uint8_t psi_b;
};

/*
9.11.3.46	Rejected NSSAI
8	7	6	5	4	3	2	1
Rejected NSSAI IEI	octet 1
Length of Rejected NSSAI contents	octet 2
Rejected S-NSSAI 1	octet 3  octet m
Rejected S-NSSAI 2	octet m+1*  octet n*
…	octet n+1*  octet u*
Rejected S-NSSAI n	octet u+1*  octet v*

Figure 9.11.3.46.1: Rejected NSSAI information element
8	7	6	5	4	3	2	1
Length of rejected S-NSSAI	Cause value	octet 1
SST	octet 2
SD	octet 3*  octet 5*
*/
struct rejected_nssai_t {
    struct nssai_t {
        bit4_t           cause;
        uint8_t          sst;
        opt_t< uint8_t > sd;
    };
    std::vector< nssai_t > nssai;
};

/*
9.11.3.47	Request type
8	7	6	5	4	3	2	1
Request type IEI	0 spare	Request type value	octet 1
*/
using request_type_t = bit3_t;

/*
9.11.3.49	Service area list
8	7	6	5	4	3	2	1
Service area list IEI	octet 1
Length of service area list contents	octet 2
Partial service area list 1	octet 3  octet i
Partial service area list 2	octet i+1*  octet l*
…	octet l+1*  octet m*
Partial service area list p	octet m+1*  octet n*

Figure 9.11.3.49.1: Service area list information element
8	7	6	5	4	3	2	1
Allowed type	Type of list	Number of elements	octet 1
MCC digit 2	MCC digit 1	octet 2
MNC digit 3	MCC digit 3	octet 3
MNC digit 2	MNC digit 1	octet 4
TAC 1	octet 5
TAC 1 (continued)	octet 6
TAC 1 (continued)	octet 7
…
TAC k	octet 3k+2*
TAC k (continued)	octet 3k+3*
TAC k (continued)	octet 3k+4*


8	7	6	5	4	3	2	1
Allowed type	Type of list	Number of elements	octet 1
MCC digit 2	MCC digit 1	octet 2
MNC digit 3	MCC digit 3	octet 3
MNC digit 2	MNC digit 1	octet 4
TAC 1	octet 5
TAC 1 (continued)	octet 6
TAC 1 (continued)	octet 7


8	7	6	5	4	3	2	1
Allowed type	Type of list	Number of elements	octet 1
MCC digit 2	MCC digit 1	octet 2
MNC digit 3	MCC digit 3	octet 3
MNC digit 2	MNC digit 1	octet 4
TAC 1	octet 5
TAC 1 (continued)	octet 6
TAC 1 (continued)	octet 7
MCC digit 2	MCC digit 1	octet 8*
MNC digit 3	MCC digit 3	octet 9*
MNC digit 2	MNC digit 1	octet 10*
TAC 2	octet 11*
TAC 2 (continued)	octet 12*
TAC 2 (continued)	octet 13*
…
MCC digit 2	MCC digit 1	octet 6k-4*
MNC digit 3	MCC digit 3	octet 6k-3*
MNC digit 2	MNC digit 1	octet 6k-2*
TAC k	octet 6k*-1
TAC k (continued)	octet 6k*
TAC k (continued)	octet 6k+1*


8	7	6	5	4	3	2	1
Allowed type	Type of list	Number of elements	octet 1
MCC digit 2	MCC digit 1	octet 2
MNC digit 3	MCC digit 3	octet 3
MNC digit 2	MNC digit 1	octet 4
*/
struct service_area_00_t {
    bit5_t number; // +1
    bit2_t type; //
    bit1_t allowed_type;//
    mcc_mnc_t mccmnc;
    std::vector< octet_3 > tac;
};
struct service_area_01_t {
    bit5_t                 number;       //
    bit2_t                 type;         //
    bit1_t                 allowed_type; //
    mcc_mnc_t              mccmnc;
    octet_3  tac;
};
struct service_area_10_t {
    struct area_t {
        mcc_mnc_t mccmnc;
        octet_3   tac;
    };

    bit5_t                number;       //
    bit2_t                type;         //
    bit1_t                allowed_type; //
    std::vector< area_t > value;
};
struct service_area_11_t {
    bit5_t    number;       // +1
    bit2_t    type;         //
    bit1_t    allowed_type; //
    mcc_mnc_t mccmnc;
};

struct service_area_t {
    bit2_t                               type;
    std::shared_ptr< service_area_00_t > l_00;
    std::shared_ptr< service_area_01_t > l_01;
    std::shared_ptr< service_area_10_t > l_10;
    std::shared_ptr< service_area_11_t > l_11;
};
struct service_area_list_t {
    std::vector< service_area_t > partial;
};

/*
9.11.3.50	Service type
8	7	6	5	4	3	2	1
Service type IEI	Service type value	octet 1
*/
using service_type_t = bit4_t;

/*
9.11.3.50A	SMS indication
8	7	6	5	4	3	2	1
SMS indication IEI	0 Spare	SAI	octet 1
*/
using sms_indication_t = bit1_t;

/*
9.11.3.51	SOR transparent container
8	7	6	5	4	3	2	1
SOR transparent container IEI	octet 1
Length of SOR transparent container contents	octet 2 octet 3
SOR header	octet 4
SOR-MAC-IAUSF	octet 5-20
CounterSOR	octet 21-22
Secured packet	octet 23* - n*

Figure 9.11.3.51.1: SOR transparent container information element for list type with value
"0" and SOR data type with value "0" 8	7	6	5	4	3	2	1 SOR transparent
container IEI	octet 1 Length of SOR transparent container contents	octet 2 octet 3
SOR header	octet 4
SOR-MAC-IAUSF	octet 5-20
CounterSOR	octet 21-22
PLMN ID and access technology list	octet 23*-102*

Figure 9.11.3.51.3: PLMN ID and access technology list
8	7	6	5	4	3	2	1
SOR transparent container IEI	octet 1
Length of SOR transparent container contents	octet 2 octet 3
SOR header	octet 4
SOR-MAC-IUE	octet 5 - 20

Figure 9.11.3.51.4: SOR transparent container information element for SOR data type with
value "1" 8	7	6	5	4	3	2	1 0 Spare	ACK	List type	List indication	SOR data
type

Figure 9.11.3.51.5: SOR header for SOR data type with value "0"
8	7	6	5	4	3	2	1
0 Spare	SOR data type	octet 4
*/

struct sor_transparent_container_0_t{
    struct plmn_id_t {
        octet_3 id;
        uint16_t access_technology_id;
    };

    // uint8_t                   header;
    bit1_t                                      sor_data_type;
    bit1_t                                      list_ind;
    bit1_t                                      list_type;
    bit1_t                                      ack;
    octet_16                                    maci;
    uint16_t counter;
    std::shared_ptr<octet_t>  packet;    // plmn-id
    std::shared_ptr< std::vector< plmn_id_t > > access_technology;
};
struct sor_transparent_container_1_t {
    //uint8_t                                     header;
    bit1_t   sor_data_type;
    octet_16 maci;
};

/*
9.11.3.53A	UE parameters update transparent container
8	7	6	5	4	3	2	1
UE parameters update transparent container IEI	octet 1
Length of UE parameters update transparent container contents	octet 2 octet 3
UE parameters update header	octet 4
UPU-MAC-IAUSF	octet 5-20
CounterUPU	octet 21-22
UE parameters update list	octet 23* - n*

Figure 9.11.3.53A.1: UE parameters update transparent container information element for UE
parameters update data type with value "0" 8	7	6	5	4	3	2	1 0 Spare	UE
parameters update data set 1 type	octet 23* Length of UE parameters update data set 1
octet 24*- 25* UE parameters update data set 1	octet 26*- x* … 0 Spare	UE parameters
update data set n type	octet y* Length of UE parameters update data set n	octet y+1*-
y+2* UE parameters update data set n	octet y+3*- n*

Figure 9.11.3.53A.2: UE parameters update list
8	7	6	5	4	3	2	1
Secured packet	octet a* - a+z*

Figure 9.11.3.53A.3: UE parameters update data set for UE parameters update data set type
with value "00000001" 8	7	6	5	4	3	2	1 Default configured NSSAI	octet b* -  c*

Figure 9.11.3.53A.5: UE parameters update transparent container information element for UE
parameters update data type with value "1" 8	7	6	5	4	3	2	1 0 Spare	REG
ACK	UPU data type

Figure 9.11.3.53A.6: UE parameters update header for UE parameters update data type with
value "0" 8	7	6	5	4	3	2	1 0 Spare	UPU data type	octet 4
*/
struct ue_parameter_update_container_0_t {
    struct item_t {
        bit4_t  type;
        octet_t dataset;
    };

    // uint8_t                   header;
    bit1_t                                      upu_data_type;
    bit1_t                                      reg;
    octet_16                                    upu_maci;
    uint16_t                                    counter;
    std::shared_ptr< std::vector< item_t > > access_technology;
};
struct ue_parameter_update_container_1_t {
    // uint8_t                                     header;
    bit1_t   upu_data_type;
    octet_16 upu_maci;
};

/*
9.11.3.54	UE security capability
8	7	6	5	4	3	2	1
UE security capability IEI	octet 1
Length of UE security capability contents	octet 2
5G-EA0	128- 5G-EA1	128- 5G-EA2	128- 5G-EA3	5G-EA4	5G-EA5	5G-EA6	5G-EA7	octet 3
5G-IA0	128- 5G-IA1	128- 5G-IA2	128- 5G-IA3	5G-IA4	5G-IA5	5G-IA6	5G-IA7	octet 4
EEA0	128- EEA1	128- EEA2	128- EEA3	EEA4	EEA5	EEA6	EEA7	octet 5*
EIA0	128- EIA1	128- EIA2	128- EIA3	EIA4	EIA5	EIA6	EIA7	octet 6*
0
Spare	octet 7* -10*
*/
struct ue_security_capability_t {
    uint8_t nea;
    uint8_t nia;
    opt_t<uint8_t> eea;
    opt_t<uint8_t> eia;
};

/*MA PD>U session information IEI	MA PDU session information value	octet 1
*/

using ma_pdu_session_information_t = bit4_t;

/*
  9.11.4.1	5GSM capability
  8	7	6	5	4	3	2	1
  5GSM capability IEI	octet 1
  Length of 5GSM capability contents	octet 2
  0 Spare	MPTCP	ATS-LL	EPT-S1	MH6-PDU	RqoS	octet 3
  0	octet 4* -15*
  Spare	octet 4* -15*
*/
struct nsm_capability_t {
    bit1_t rqos;
    bit1_t mh6_pdu;
    bit1_t ept_s1;
    bit1_t ats_ll;
    bit1_t mptcp;
};

/*
  9.11.4.2	5GSM cause
  8	7	6	5	4	3	2	1
  5GSM cause IEI	octet 1
  Cause value	octet 2
*/
using nsm_cause_t = uint8_t;

/*
  9.11.4.3	Always-on PDU session indication
  8	7	6	5	4	3	2	1
  Always-on PDU session indication IEI	0 Spare	APSI	octet 1
*/
struct always_on_pdu_session_indication_t {
    bit1_t apsi;
};

/*
  9.11.4.4	Always-on PDU session requested
  8	7	6	5	4	3	2	1
  Always-on PDU session requested IEI	0 Spare	APSR	octet 1
*/
struct always_on_pdu_session_requested_t {
    bit1_t apsr;
};

/*
  9.11.4.5	Allowed SSC mode
  8	7	6	5	4	3	2	1
  Allowed SSC mode IEI	0 Spare	SSC3	SSC2	SSC1	octet 1
*/
using allowed_ssc_mode_t = bit3_t;

/*
  9.11.4.7	Integrity protection maximum data rate
  8	7	6	5	4	3	2	1
  Integrity protection maximum data rate IEI	octet 1
  Maximum data rate per UE for user-plane integrity protection for uplink	octet 2
  Maximum data rate per UE for user-plane integrity protection for downlink	octet 3
*/
struct integrity_protection_maximum_data_rate_t {
    uint8_t uplink;
    uint8_t downlink;
};

/*
  9.11.4.9	Maximum number of supported packet filters
  8	7	6	5	4	3	2
  Maximum number of supported packet filters IEI
  Maximum number of supported packet filters
  Maximum number of supported packet filters (continued)	0 Spare
*/
using bit11_t                                   = uint16_t;
using supported_packet_filters_maximum_number_t = bit11_t;

/*
  9.11.4.11	PDU session type
  8	7	6	5	4	3	2	1
  PDU session type IEI	0 Spare	PDU session type value	octet 1
*/
using pdu_session_type_t = bit3_t;

/*
  9.11.4.12	QoS flow descriptions
  8	7	6	5	4	3	2	1
  QoS flow descriptions IEI	octet 1
  Length of QoS flow descriptions contents	octet 2  octet 3
  QoS flow description 1	octet 4  octet u
  QoS flow description 2	octet u+1  octet v
  ...	octet v+1  octet w
  QoS flow description n	octet w+1  octet x

  Figure 9.11.4.12.1: QoS flow descriptions information element
  8	7	6	5	4	3	2
  0 Spare	QFI
  Operation code	0 Spare
  0 Spare	E	Number of parameters
  Parameters list

  Figure 9.11.4.12.2: QoS flow description
  8	7	6	5	4	3	2	1
  Parameter 1	octet 7  octet m
  Parameter 2	octet m+1  octet n
  ...	octet n+1  octet o
  Parameter n	octet o+1  octet u

  Figure 9.11.4.12.3: Parameters list
  8	7	6	5	4	3	2	1
  Parameter identifier	octet 7
  Length of parameter contents	octet 8
  Parameter contents	octet 9  octet m
*/
struct qos_flow_description_t {
    struct parameter_t {
        uint8_t id;
        octet_t content;
    };
    struct entry_t {
        bit6_t qfi;
        bit3_t opcode;
        bit1_t ebit;
        std::vector< parameter_t > parameters;
    };
    std::vector< entry_t > fds;
};

/*
  9.11.4.14	Session-AMBR
  8	7	6	5	4	3	2	1
  Session-AMBR IEI	octet 1
  Length of Session-AMBR contents	octet 2
  Unit for Session-AMBR for downlink	octet 3
  Session-AMBR for downlink	octet 4-5
  Unit for Session-AMBR for uplink	octet 6
  Session-AMBR for uplink	octet 7-8
*/
struct session_ambr_t {
    uint8_t downlink_unit;
    uint16_t downlink;
    uint8_t  uplink_unit;
    uint16_t uplink;
};

/*
  8	7	6	5	4	3	2	1
  SM PDU DN request container information IEI	octet 1
  SM PDU DN request container information length	octet 2
  DN-specific identity	octets 3*-n*
*/
using sm_pdu_dn_request_container_t = octet_t;

/*
  9.11.4.16	SSC mode
  8	7	6	5	4	3	2	1
  SSC mode IEI	0 Spare	SSC mode value	octet 1
*/
using ssc_mode_t = bit3_t;

/*
  9.11.4.17	Re-attempt indicator
  8	7	6	5	4	3	2
  Re-attempt indicator IEI
  Length of Re-attempt indicator contents
  0 Spare	EPLMNC	RATC
*/
struct reattempt_indicator_t {
    bit1_t ratc;
    bit1_t eplmnc;
};

/*
  9.11.4.18	5GSM network feature support
  8	7	6	5	4	3	2	1
  5GSM network feature support IEI	octet 1
  Length of 5GSM network feature support contents	octet 2
  0 Spare	EPT-S1	octet 3
  0	octet 4* -15*
  Spare	octet 4* -15*
*/
using nsm_network_feature_support_t = bit1_t;

/*
  9.11.4.19	Session-TMBR
  8	7	6	5	4	3	2	1
  Session-TMBR IEI	octet 1
  Length of Session-TMBR contents	octet 2
  Unit for Session-TMBR for downlink	octet 3
  Session-TMBR for downlink	octet 4-5
  Unit for Session-TMBR for uplink	octet 6
  Session-TMBR for uplink	octet 7-8
*/
struct session_tmbr_t {
    uint8_t downlink_unit;
    uint16_t downlink;
    uint8_t  uplink_unit;
    uint16_t uplink;
};

/*
  9.11.4.21	5GSM congestion re-attempt indicator
  8	7	6	5	4	3	2
  5GSM congestion re-attempt indicator IEI
  Length of 5GSM congestion re-attempt indicator contents
  0 Spare	ABO
*/
using nsm_congestion_reattempt_indicator_t = bit1_t;

/*
  9.11.4.22	ATSSS container
  8	7	6	5	4	3	2	1
  ATSSS container IEI	octet 1
  Length of ATSSS container contents	octet 2 octet 3
  ATSSS container contents	octet 4  octet x
*/
using atsss_container_t = octet_t;

/*
  9.11.4.23	Control plane only indication
  8	7	6	5	4	3	2	1
  Control plane only indication IEI	0 Spare	CPOI value	octet 1
*/
using control_plane_only_indication_t = bit1_t;
